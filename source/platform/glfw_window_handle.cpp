
#include "platform/glfw_window_handle.hpp"

#include "config.hpp"
#include "opengl_bindings.hpp"
#ifdef __EMSCRIPTEN__
#  include <emscripten/html5.h>
#endif

#include <iostream>
#include <stdexcept>

namespace fractal {

#ifdef __EMSCRIPTEN__

static bool
static_resize_callback(int, const EmscriptenUiEvent*, void* data)
{
    double css_width, css_height;
    emscripten_get_element_css_size("#canvas", &css_width, &css_height);
    double dpr = emscripten_get_device_pixel_ratio();
    float fb_w = static_cast<float>(css_width * dpr);
    float fb_h = static_cast<float>(css_height * dpr);
    emscripten_set_canvas_element_size(
        "#canvas", static_cast<int>(fb_w), static_cast<int>(fb_h)
    );
    auto* handle = static_cast<GlfwWindowHandle*>(data);
    handle->resize_callback(fb_w, fb_h);

    return true;
}

#else

void
static_resize_callback(GLFWwindow* window, int width, int height)
{
    auto* handle = static_cast<GlfwWindowHandle*>(glfwGetWindowUserPointer(window));
    handle->resize_callback(static_cast<float>(width), static_cast<float>(height));
}
#endif

void
GlfwWindowHandle::resize_callback(float width, float height)
{
    if (static_cast<int>(width) != static_cast<int>(width_)
        || static_cast<int>(height_) != static_cast<int>(height)) {
        has_resized_ = true;
    }
    width_ = width;
    height_ = height;
    glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
}

GlfwWindowHandle::GlfwWindowHandle(
    int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share
) : WINDOW{glfwCreateWindow(width, height, title, monitor, share)}
{
    if (WINDOW == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(WINDOW);

#ifndef __EMSCRIPTEN__
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSetWindowUserPointer(WINDOW, this);
    glfwSetFramebufferSizeCallback(WINDOW, static_resize_callback);

    resize_callback(WIDTH, HEIGHT);
#else
    emscripten_set_resize_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_TRUE, static_resize_callback
    );
#endif
}

void
GlfwWindowHandle::on_first()
{
#ifdef __EMSCRIPTEN__
    static_resize_callback(0, nullptr, this);
#endif
}

bool
GlfwWindowHandle::has_resized()
{
    if (has_resized_) {
        has_resized_ = false;
        return true;
    }
    return false;
}

GlfwWindowHandle::~GlfwWindowHandle()
{
    glfwDestroyWindow(WINDOW);
}

} // namespace fractal
