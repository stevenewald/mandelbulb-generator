#include "glfw_handle.hpp"

#include "util.hpp"

#include <GLFW/glfw3.h>

namespace fractal {
GlfwHandle::GlfwHandle()
{
    if (glfwInit() == GLFW_FALSE) {
        fatal_error("Failed to initialize glfw");
    }

    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GlfwHandle::~GlfwHandle()
{
    glfwTerminate();
}

} // namespace fractal
