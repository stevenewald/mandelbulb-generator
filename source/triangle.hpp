#pragma once

#include "shader.hpp"

#include <glad/glad.h>

#include <array>
#include <iostream>
#include <string>

namespace fractal {
unsigned int
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
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "iResolution");
    glUseProgram(shaderProgram);
    glUniform2f(vertexColorLocation, 800.0f, 600.0f);

    return shaderProgram;
}

unsigned int
run_program()
{
    auto program = compile_program();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO);

    return program;
}

} // namespace fractal
