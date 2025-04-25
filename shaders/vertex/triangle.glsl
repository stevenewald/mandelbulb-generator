#version 330 core
layout(location = 0) in vec3 aPos;
out vec2 pos;

uniform vec2 resolution;

void
main()
{
    const vec2 vertices[3] =
        vec2[3](vec2(-1.0, -1.0), vec2(3.0, -1.0), vec2(-1.0, 3.0));
    vec2 p = vertices[gl_VertexID];
    gl_Position = vec4(p, 0.0, 1.0);
    pos = (gl_Position.xy * .5 + .5) * resolution;
}
