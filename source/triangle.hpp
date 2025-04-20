#pragma once

#include "shader.hpp"

#include <glad/glad.h>

#include <array>
#include <iostream>
#include <string>

namespace fractal {
void
compile_program()
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    auto vertex = create_shader("shaders/vertex/triangle.glsl", ShaderType::vertex);
    auto fragment =
        create_shader("shaders/fragment/triangle.glsl", ShaderType::fragment);

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

    std::array vertices{-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
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
