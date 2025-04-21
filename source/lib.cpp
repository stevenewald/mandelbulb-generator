#include "lib.hpp"

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
float pos[3] = {0.0f, 0.0f, 2.0f};
float delta = 0.01f;

void
process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos[0] += delta;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos[0] -= delta;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos[1] += delta;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos[1] -= delta;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        pos[2] -= delta;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        pos[2] += delta;
}
} // namespace

void
run()
{
    fractal::GlfwContextHandle glfw_context_handle;

    fractal::GlfwWindowHandle glfw_window_handle =
        fractal::create_window_handle(800, 600, "GL Test", nullptr, nullptr);
    if (glfw_window_handle.get() == nullptr) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }
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
    int vertex_ro_location = prog.get_uniform_location("ro");
    prog.use();
    glUniform2f(vertex_res_location, 800.0f, 600.0f);

    // Main loop
    while (!glfwWindowShouldClose(glfw_window_handle.get())) {
        glfwPollEvents();

        process_input(glfw_window_handle.get());

        // Clear the screen with a red background.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers to display the rendered frame.
        glfwSwapBuffers(glfw_window_handle.get());

        glUniform1f(vertex_time_location, t);
        glUniform3f(vertex_ro_location, pos[0], pos[1], pos[2]);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        t += .01f;
    }
}
