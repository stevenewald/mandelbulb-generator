#pragma once

#include "shader.hpp"

#include <glad/glad.h>

#include <array>
#include <iostream>
#include <string>

namespace fractal {
const char* const vert = R"(#version 330 core
layout (location = 0) in vec3 aPos;
		out vec4 pos;
void main()
{
gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		pos = gl_Position;
})";

const char* const frag = R"(#version 330 core
in vec4 pos;
out vec4 FragColor;
void main()
{
FragColor = vec4(pos.x+.5f, pos.y+0.5f, pos.z+0.5f, 1.0f);
})";

void
compile_program()
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    auto vertex = Shader(vert, ShaderType::vertex);
    auto fragment = Shader(frag, ShaderType::fragment);

    glAttachShader(shaderProgram, vertex.get_id());
    glAttachShader(shaderProgram, fragment.get_id());
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glUseProgram(shaderProgram);
}

void
run_program()
{
    compile_program();

    std::array vertices{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

} // namespace fractal
