#include "lib.hpp"

#include "handles/glfw_context_handle.hpp"
#include "handles/glfw_window_handle.hpp"
#include "triangle.hpp"

#include <fmt/core.h>
#include <glad/glad.h>

#include <iostream>
#include <string>

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

    fractal::run_program();

    // Main loop
    while (!glfwWindowShouldClose(glfw_window_handle.get())) {
        glfwPollEvents();

        // Clear the screen with a red background.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers to display the rendered frame.
        glfwSwapBuffers(glfw_window_handle.get());
    }

    glfwDestroyWindow(glfw_window_handle.get());
}
