#pragma once

#include "config.hpp"
#include "math/camera.hpp"
#include "mouse_tracker.hpp"
#include "platform/glfw_context_handle.hpp"
#include "platform/glfw_window_handle.hpp"
#include "render/camera_uniform_buffer.hpp"
#include "render/cubemap.hpp"
#include "render/program.hpp"

namespace fractal {

class App {
public:
    GlfwContextHandle glfw_context;
    GlfwWindowHandle glfw_window{WIDTH, HEIGHT, "Mandelbulb", nullptr, nullptr};
    Program program = create_fractal_program(VERTEX_PATH, FRAGMENT_PATH);
    Camera camera{START_YAW};
    CameraUBO camera_ubo;
    Cubemap cube{CUBEMAP_IMAGES};
    MouseTracker tracker;

    static Program create_fractal_program(
        const std::filesystem::path& vertex_path, const std::filesystem::path& fragment
    );
    void initialize_uniforms_();

    App();
};

} // namespace fractal
