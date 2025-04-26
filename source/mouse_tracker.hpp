#pragma once

#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>

namespace fractal {
class MouseTracker {
    double start_x_{};
    double start_y_{};
    double dragged_x_{};
    double dragged_y_{};
    bool dragging_{};

public:
    void
    tick(GLFWwindow* window)
    {
        double x_pos{};
        double y_pos{};
        glfwGetCursorPos(window, &x_pos, &y_pos);
        if (dragging_) {
            dragged_x_ += (start_x_ - x_pos);
            dragged_y_ += (start_y_ - y_pos);
            start_x_ = x_pos;
            start_y_ = y_pos;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (!dragging_) {
                start_x_ = x_pos;
                start_y_ = y_pos;
                dragging_ = true;
            }
        }
        else {
            if (dragging_) {
                dragging_ = false;
            }
        }
    }

    std::pair<float, float>
    get_and_reset_dragged()
    {
        std::pair<float, float> dragged{dragged_x_, dragged_y_};
        dragged_x_ = 0;
        dragged_y_ = 0;
        return dragged;
    }
};
} // namespace fractal
