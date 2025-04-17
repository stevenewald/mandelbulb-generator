#pragma once

#include <GLFW/glfw3.h>

#include <memory>

namespace fractal {
using GlfwWindowHandle = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

GlfwWindowHandle
create_window_handle(
    int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share
)
{
    return {glfwCreateWindow(width, height, title, monitor, share), &glfwDestroyWindow};
}
} // namespace fractal
