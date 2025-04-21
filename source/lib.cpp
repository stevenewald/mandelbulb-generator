#include "lib.hpp"

#include "camera.hpp"
#include "camera_ubo.hpp"
#include "handles/glfw_context_handle.hpp"
#include "handles/glfw_window_handle.hpp"
#include "triangle.hpp"

#include <fmt/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <thread>

library::library() : name{fmt::format("{}", "mandelbulb-generator")} {}

namespace {
float delta = 0.01f;
fractal::Camera camera{};

void
process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.modify_yaw(delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.modify_yaw(-delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.modify_pitch(-delta);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.modify_pitch(delta);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.modify_radius(-delta);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.modify_radius(delta);
}

} // namespace

void
run()
{
    fractal::GlfwContextHandle glfw_context_handle;

    fractal::GlfwWindowHandle glfw_window_handle =
        fractal::create_window_handle(800, 600, "Mandelbulb", nullptr, nullptr);
    glfwMakeContextCurrent(glfw_window_handle.get());

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    auto prog = fractal::run_program();

    float t{};
    int vertex_time_location = prog.get_uniform_location("iTime");
    int vertex_res_location = prog.get_uniform_location("iResolution");

    fractal::CameraUBO camera_ubo{};
    camera_ubo.attachToShader(prog, "CameraData");
    prog.use();
    glUniform2f(vertex_res_location, 800.0f, 600.0f);

    // Main loop
    while (!glfwWindowShouldClose(glfw_window_handle.get())) {
        glfwPollEvents();

        process_input(glfw_window_handle.get());
        camera_ubo.update(camera.get_args(600.0f));
        camera_ubo.bind();

        // Clear the screen with a red background.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers to display the rendered frame.
        glfwSwapBuffers(glfw_window_handle.get());

        glUniform1f(vertex_time_location, t);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        t += .01f;
    }
}
