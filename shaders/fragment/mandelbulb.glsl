#version 300 es
precision highp float;
in vec2 pos;
out vec4 fragColor;

uniform vec2 resolution;
uniform samplerCube skybox;

uniform CameraData
{
    vec3 camera_position;
    vec3 camera_right;
    vec3 camera_up;
    vec3 image_plane_center;
    vec3 sun_direction;
};

#define MAX_DIST  400.0
#define MAX_STEPS 500
#define EPSILON   0.0001
#define Power     5.0

vec3
palette(float t, vec3 a, vec3 b, vec3 c, vec3 d)
{
    return a + b * cos(6.28318 * (c * t + d));
}

vec4
colorForQ(int steps)
{
    float t = float(steps);
    vec3 A = vec3(0.8, .5, .4);
    vec3 B = vec3(0.2, .4, .2);
    vec3 C = vec3(2.0 / 14.0, 1.0 / 14.0, 1.0 / 14.0);
    vec3 D = vec3(0, .25, .25);
    return vec4(palette(t, A, B, C, D), 1.0);
}

float
SDF(vec3 pos, out int steps)
{
    vec3 z = pos;
    float dr = 1.0;
    float r = 0.0;
    for (int i = 0; i < 20; i++) {
        r = length(z);
        steps = i;
        if (r > 2.0)
            break;

        // convert to polar coordinates
        float theta = acos(z.z / r);
        float phi = atan(z.y, z.x);
        dr = pow(r, Power - 1.0) * Power * dr + 1.0;

        // scale and rotate the point
        float zr = pow(r, Power);
        theta = theta * Power;
        phi = phi * Power;

        // convert back to cartesian coordinates
        z = zr * vec3(sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta));
        z += pos;
    }

    return 0.5 * log(r) * r / dr;
}

float
trace(vec3 ro, vec3 rd, out int steps)
{
    float depth = max(length(ro) - 2.0, 0.0);

    for (int i = 0; i < MAX_STEPS; ++i) {
        float dist = SDF(ro + depth * rd, steps);

        if (dist < EPSILON)
            return depth;

        depth += dist;

        if (depth > MAX_DIST)
            return MAX_DIST;
    }

    return MAX_DIST;
}

float
mapDistance(vec3 p)
{
    int dummy;
    return SDF(p, dummy);
}

// central‐difference normal estimation
vec3
estimateNormal(vec3 p)
{
    // slightly larger epsilon for gradient sampling
    float h = EPSILON * 10.0;
    return normalize(vec3(
        mapDistance(p + vec3(h, 0, 0)) - mapDistance(p - vec3(h, 0, 0)),
        mapDistance(p + vec3(0, h, 0)) - mapDistance(p - vec3(0, h, 0)),
        mapDistance(p + vec3(0, 0, h)) - mapDistance(p - vec3(0, 0, h))
    ));
}

// number of soft‐shadow samples
const int SHADOW_STEPS = 256;
const float SHADOW_K = 32.0;
const float SHADOW_EPS = EPSILON * 2.0;

float
softshadow(vec3 ro, vec3 rd)
{
    float res = 1.0;
    float t = SHADOW_EPS;
    for (int i = 0; i < SHADOW_STEPS; ++i) {
        float h = mapDistance(ro + rd * t);
        res = min(res, SHADOW_K * h / t);
        t += clamp(h, SHADOW_EPS, 0.2);
        if (res < 0.01 || t > MAX_DIST)
            break;
    }
    return clamp(res, 0.6, 1.0);
}

#define AO_SAMPLES 8
#define AO_STEP    0.10
#define AO_DECAY   0.71

float
ambientocclusion(vec3 ro, vec3 normal)
{
    float occlusion = 0.0;
    float weight = 1.0;

    // march out along the normal, sampling scene distance
    for (int i = 1; i <= AO_SAMPLES; ++i) {
        float dist = AO_STEP * float(i);
        float sceneD = mapDistance(ro + normal * dist);
        // accumulate how much the geometry encroaches into the sample sphere
        occlusion += (dist - sceneD) * weight;
        weight *= AO_DECAY;
    }

    // invert and clamp to [0,1]
    return clamp(1.0 - pow(occlusion, 5.0), 0.5, 1.0);
}

void
main()
{
    vec2 xy = pos.xy - resolution.xy * 0.5;

    // assemble ray
    vec3 rd = normalize(xy.x * camera_right + xy.y * camera_up + image_plane_center);
    int p_steps = 0;
    float dist = trace(camera_position, rd, p_steps);
    if (dist < MAX_DIST) {
        vec3 p = camera_position + rd * dist;
        vec3 n = estimateNormal(p);
        float sh = softshadow(p + n * EPSILON * 5.0, sun_direction);
        float ao = ambientocclusion(p + n * EPSILON * 5.0, n);
        fragColor = colorForQ(p_steps);
        fragColor.xyz *= sh;
        fragColor.xyz *= ao;
        return;
    }

    fragColor = texture(skybox, rd);
}
