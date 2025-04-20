#pragma once

#include "program.hpp"
#include "shader.hpp"

#include <glad/glad.h>

#include <array>
#include <iostream>
#include <string>

namespace fractal {
Program
run_program()
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO);

    std::filesystem::path vertex = "shaders/vertex/triangle.glsl";
    std::filesystem::path fragment = "shaders/fragment/triangle.glsl";

    return Program{vertex, fragment};
}

} // namespace fractal
