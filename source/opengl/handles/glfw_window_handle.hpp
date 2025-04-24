#pragma once

#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>

namespace fractal {
using GlfwWindowHandle = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

GlfwWindowHandle
create_window_handle(
    int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share
)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
    if (window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    return {window, &glfwDestroyWindow};
}
} // namespace fractal
