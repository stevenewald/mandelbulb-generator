#include "platform/glfw_context_handle.hpp"

#include <GLFW/glfw3.h>

#include <stdexcept>

namespace fractal {
GlfwContextHandle::GlfwContextHandle()
{
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Failed to initialize glfw");
    }

    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GlfwContextHandle::~GlfwContextHandle()
{
    glfwTerminate();
}

} // namespace fractal
