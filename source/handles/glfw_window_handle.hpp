#pragma once

#include "handles/shader.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <stdexcept>

namespace fractal {
using GlfwWindowHandle = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

void
make_current_context(const GlfwWindowHandle& handle)
{
    glfwMakeContextCurrent(handle.get());
}

GlfwWindowHandle
create_window_handle(
    int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share
)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
    if (window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    // Load OpenGL functions with GLAD
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    return {window, &glfwDestroyWindow};
}

} // namespace fractal
