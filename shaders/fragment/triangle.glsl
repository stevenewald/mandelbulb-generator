#version 330 core
in vec2 pos;
out vec4 FragColor;
void main()
{
    FragColor = vec4(pos.x + 1.0f, pos.y + 1.0f, pos.x - pos.y, 1.0f);
}
