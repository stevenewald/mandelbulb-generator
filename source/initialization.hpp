#pragma once

#include "camera.hpp"
#include "camera_ubo.hpp"
#include "config.hpp"
#include "handles/cubemap.hpp"
#include "handles/glfw_context_handle.hpp"
#include "handles/glfw_window_handle.hpp"
#include "handles/program.hpp"

namespace fractal {
Program
create_fractal_program()
{
    unsigned int vao{};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    std::filesystem::path vertex = "shaders/vertex/single_triangle.glsl";
    std::filesystem::path fragment = "shaders/fragment/mandelbulb.glsl";

    return Program{vertex, fragment};
}

struct app {
    GlfwContextHandle glfw_context;
    GlfwWindowHandle glfw_window =
        create_window_handle(WIDTH, HEIGHT, "Mandelbulb", nullptr, nullptr);
    Program program = create_fractal_program();
    Camera camera{START_YAW};
    CameraUBO camera_ubo;
    Cubemap cube{CUBEMAP_IMAGES};
};

void
initialize_uniforms(const Program& program)
{
    int vertex_res_location = program.get_uniform_location("resolution");
    glUniform2f(vertex_res_location, WIDTH, HEIGHT);

    int vertex_skybox_location = program.get_uniform_location("skybox");
    glUniform1i(vertex_skybox_location, 0);
}

} // namespace fractal
