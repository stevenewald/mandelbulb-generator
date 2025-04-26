#pragma once

#include "camera.hpp"
#include "camera_ubo.hpp"
#include "config.hpp"
#include "handles/cubemap.hpp"
#include "handles/glfw_context_handle.hpp"
#include "handles/glfw_window_handle.hpp"
#include "handles/program.hpp"
#include "mouse_tracker.hpp"

namespace fractal {

void
create_dummy_attribute_array()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttrib2f(0, 0.0f, 0.0f);
    glBindVertexArray(0);
}

Program
create_fractal_program(
    const std::filesystem::path& vertex, const std::filesystem::path& fragment
)
{
    unsigned int vao{};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return Program{vertex, fragment};
}

struct app {
    GlfwContextHandle glfw_context;
    GlfwWindowHandle glfw_window{WIDTH, HEIGHT, "Mandelbulb", nullptr, nullptr};
    Program program = create_fractal_program(VERTEX_PATH, FRAGMENT_PATH);
    Camera camera{START_YAW};
    CameraUBO camera_ubo;
    Cubemap cube{CUBEMAP_IMAGES};
    MouseTracker tracker;
};

void
initialize_uniforms(const Program& program)
{
    int vertex_skybox_location = program.get_uniform_location("skybox");
    glUniform1i(vertex_skybox_location, 0);
}

} // namespace fractal
