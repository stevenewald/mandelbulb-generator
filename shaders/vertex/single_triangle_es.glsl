#version 300 es
out vec2 pos;
uniform vec2 resolution;

void
main()
{
    // WebGL2 array constructor syntax:
    const vec2 vertices[3] = vec2[](vec2(-1.0, -1.0), vec2(3.0, -1.0), vec2(-1.0, 3.0));
    vec2 p = vertices[int(gl_VertexID)];
    gl_Position = vec4(p, 0.0, 1.0);
    pos = (p * 0.5 + 0.5) * resolution;
}
