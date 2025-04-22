#version 330 core
in vec2 pos;
out vec4 fragColor;

uniform vec2 iResolution;
uniform float iTime;
uniform samplerCube skybox;

uniform CameraData {
vec3 camPos;
vec3 right;
vec3 up;
vec3 z;
vec3 sunDirection;
};

#define MAX_DIST 400.0
#define MAX_STEPS 500
#define EPSILON 0.0001
#define Power 3

vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d){
    return a + b * cos(6.28318 * (c * t + d));
}

vec4 colorForQ(int steps){
    float t = clamp(float(steps) / 20, 0.0, 1.0);
    // tweak these to taste:
    vec3 A = vec3(0.8, .5, .4);
    vec3 B = vec3(0.2, .4, .2);
    vec3 C = vec3(2.0, 1.0, 1.0);
    vec3 D = vec3(0, .25, .25);
    return vec4(palette(t, A, B, C, D), 1.0);
}

float SDF(vec3 pos, out int steps) {
	vec3 z = pos;
	float dr = 1.0;
	float r = 0.0;
	for (int i = 0; i < 20 ; i++) {
		r = length(z);
        steps = i;
		if (r>4.0) break;
		
		// convert to polar coordinates
		float theta = acos(z.z/r);
		float phi = atan(z.y,z.x);
		dr =  pow( r, Power-1.0)*Power*dr + 1.0;
		
		// scale and rotate the point
		float zr = pow( r,Power);
		theta = theta*Power;
		phi = phi*Power;
		
		// convert back to cartesian coordinates
		z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
		z+=pos;
	}

	return 0.5*log(r)*r/dr;
}

float trace(vec3 ro, vec3 rd, out int steps) {
  float depth = 0.0;

  for (int i = 0; i < MAX_STEPS; ++i) {
    float dist = SDF(ro + depth * rd, steps);

    if (dist < EPSILON) return depth;

    depth += dist;

    if (depth > MAX_DIST) return MAX_DIST;
  }

  return MAX_DIST;
}

float mapDistance(vec3 p) {
    int dummy;
    return SDF(p, dummy);
}

// central‐difference normal estimation
vec3 estimateNormal(vec3 p) {
    // slightly larger epsilon for gradient sampling
    float h = EPSILON * 10.0;
    return normalize(vec3(
        mapDistance(p + vec3( h,0,0)) - mapDistance(p - vec3( h,0,0)),
        mapDistance(p + vec3(0, h,0)) - mapDistance(p - vec3(0, h,0)),
        mapDistance(p + vec3(0,0, h)) - mapDistance(p - vec3(0,0, h))
    ));
}

void main()
{
	vec2 xy = pos.xy - iResolution.xy * 0.5;

	// assemble ray
	vec3 rd = normalize(
		xy.x * right +
		xy.y * up +
		z
	);
	int p_steps = 0;

	float dist = trace(camPos, rd, p_steps);

	if (dist < MAX_DIST) {
        vec3 p = camPos + rd * dist;

        vec3 n = estimateNormal(p);
        vec3 ro_shadow = p + n * (EPSILON * 5.0);

        int shadow_steps = 0;
        float sundist = trace(ro_shadow, sunDirection, shadow_steps);

        if (sundist < MAX_DIST) {
            fragColor = vec4(0,0,0,1);  // in shadow
        } else {
            fragColor = colorForQ(p_steps);
        }
        return;
    }

	fragColor = texture(skybox, rd);
}
