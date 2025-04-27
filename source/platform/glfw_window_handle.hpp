#pragma once

#include "opengl_bindings.hpp"

namespace fractal {

class GlfwWindowHandle {
    GLFWwindow* const WINDOW;
    float width_{};
    float height_{};
    bool has_resized_{};

public:
    void resize_callback(float width, float height);
    GlfwWindowHandle(
        int width, int height, const char* title, GLFWmonitor* monitor,
        GLFWwindow* share
    );

    void on_first();

    bool has_resized();

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

    GLFWwindow*
    get_window() const
    {
        return WINDOW;
    }

    GlfwWindowHandle(const GlfwWindowHandle&) = delete;
    GlfwWindowHandle(GlfwWindowHandle&&) = delete;
    GlfwWindowHandle& operator=(const GlfwWindowHandle&) = delete;
    GlfwWindowHandle& operator=(GlfwWindowHandle&&) = delete;

    ~GlfwWindowHandle();
};

} // namespace fractal
