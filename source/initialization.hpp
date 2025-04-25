#pragma once

#include "camera.hpp"
#include "camera_ubo.hpp"
#include "config.hpp"
#include "handles/glfw_context_handle.hpp"
#include "handles/glfw_window_handle.hpp"
#include "program.hpp"
#include "shader.hpp"
#include "triangle.hpp"

#include <iostream>

namespace fractal {
struct app {
    GlfwContextHandle glfw_context;
    GlfwWindowHandle glfw_window =
        create_window_handle(WIDTH, HEIGHT, "Mandelbulb", nullptr, nullptr);
    Program program = create_fractal_program();
    Camera camera{START_YAW};
    CameraUBO camera_ubo;
};

void
initialize_uniforms(const Program& program)
{
    unsigned int vertex_res_location = program.get_uniform_location("resolution");
    glUniform2f(vertex_res_location, WIDTH, HEIGHT);

    int vertex_skybox_location = program.get_uniform_location("skybox");
    glUniform1i(vertex_skybox_location, 0);
}
} // namespace fractal
