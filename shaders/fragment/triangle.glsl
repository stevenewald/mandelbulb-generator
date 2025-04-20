#version 330 core
in vec2 pos;
out vec4 fragColor;

uniform vec2 iResolution;
uniform float iTime;

#define MAX_DIST 100.0
#define MAX_STEPS 200
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

void main()
{
	vec2 xy = pos - iResolution.xy / 2.0;
	vec3 ro = vec3(0.25 * cos(iTime), 0.5 * sin(iTime), 2.0 + .8 * sin(iTime / 3.0));
	vec3 rd = normalize(vec3(xy, -iResolution.y / tan(radians(50.0) / 2.0)));
	int steps = 0;

	float dist = trace(ro, rd, steps);

	if (dist < MAX_DIST) {
		fragColor = colorForQ(steps);
		return;
	}

	fragColor = vec4(vec3(0.0), 1.0);
}
