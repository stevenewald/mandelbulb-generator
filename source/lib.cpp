#include "lib.hpp"

#include "handles/glfw_context_handle.hpp"
#include "handles/glfw_window_handle.hpp"
#include "triangle.hpp"

#include <fmt/core.h>
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <thread>

library::library() : name{fmt::format("{}", "mandelbulb-generator")} {}

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
    int vertexTimeLocation = glGetUniformLocation(prog, "iTime");

    // Main loop
    while (!glfwWindowShouldClose(glfw_window_handle.get())) {
        glfwPollEvents();

        // Clear the screen with a red background.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers to display the rendered frame.
        glfwSwapBuffers(glfw_window_handle.get());

        glUniform1f(vertexTimeLocation, t);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        t += .01f;
    }

    glfwDestroyWindow(glfw_window_handle.get());
}
