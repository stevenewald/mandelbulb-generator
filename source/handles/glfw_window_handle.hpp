#pragma once

#include "opengl_bindings.hpp"
#ifdef __EMSCRIPTEN__
#  include <emscripten/html5.h>
#endif

#include <iostream>
#include <stdexcept>

namespace fractal {

class GlfwWindowHandle {
    GLFWwindow* const WINDOW;
    float width_{};
    float height_{};
    bool has_resized_{};

#ifdef __EMSCRIPTEN__

    static bool
    resize_callback(int, const EmscriptenUiEvent*, void* data)
    {
        auto* handle = static_cast<GlfwWindowHandle*>(data);
        handle->emscripten_resize_callback_();

        return true;
    }

    void
    emscripten_resize_callback_()
    {
        double css_width, css_height;
        emscripten_get_element_css_size("#canvas", &css_width, &css_height);
        double dpr = emscripten_get_device_pixel_ratio();
        float fb_w = static_cast<float>(css_width * dpr);
        float fb_h = static_cast<float>(css_height * dpr);
        emscripten_set_canvas_element_size(
            "#canvas", static_cast<int>(fb_w), static_cast<int>(fb_h)
        );
        glViewport(0, 0, static_cast<int>(fb_w), static_cast<int>(fb_h));

        resize_callback_(fb_w, fb_h);
    }
#else

    static void
    resize_callback(GLFWwindow* window, int width, int height)
    {
        auto* handle = static_cast<GlfwWindowHandle*>(glfwGetWindowUserPointer(window));
        handle->resize_callback_(static_cast<float>(width), static_cast<float>(height));
    }
#endif

    void
    resize_callback_(float width, float height)
    {
        if (static_cast<int>(width) != static_cast<int>(width_)
            || static_cast<int>(height_) != static_cast<int>(height)) {
            has_resized_ = true;
        }
        width_ = width;
        height_ = height;
    }

public:
    GlfwWindowHandle(
        int width, int height, const char* title, GLFWmonitor* monitor,
        GLFWwindow* share
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
        glfwSetFramebufferSizeCallback(WINDOW, resize_callback);

        resize_callback_(WIDTH, HEIGHT);
#else
        emscripten_set_resize_callback(
            EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_TRUE,
            GlfwWindowHandle::resize_callback
        );
#endif
    }

    void
    on_first()
    {
#ifdef __EMSCRIPTEN__
        emscripten_resize_callback_();
#endif
    }

    bool
    has_resized()
    {
        if (has_resized_) {
            has_resized_ = false;
            return true;
        }
        return false;
    }

    float
    get_width() const
    {
        return width_;
    }

    float
    get_height() const
    {
        return height_;
    }

    GlfwWindowHandle(const GlfwWindowHandle&) = delete;
    GlfwWindowHandle(GlfwWindowHandle&&) = delete;
    GlfwWindowHandle& operator=(const GlfwWindowHandle&) = delete;
    GlfwWindowHandle& operator=(GlfwWindowHandle&&) = delete;

    ~GlfwWindowHandle() { glfwDestroyWindow(WINDOW); }

    GLFWwindow*
    get_window() const
    {
        return WINDOW;
    }
};

} // namespace fractal
