#pragma once

#include "render/uniform_camera_args.hpp"

#include <GLFW/glfw3.h>

#include <utility>

namespace fractal {
class Camera {
    static constexpr float DELTA = 0.01f;
    static constexpr float MIN_RADIUS = 3.0f;
    static constexpr float MAX_RADIUS = 10.0f;
    float radius_ = 5.0f;
    float pitch_ = 0.0001f;
    float yaw_;

public:
    explicit Camera(float start_yaw = 0.0f) : yaw_{start_yaw} {}

    void modify_yaw(float delta);
    void modify_pitch(float delta);
    void modify_radius(float delta);

    bool process_input(GLFWwindow* window);
    bool process_input(std::pair<float, float> mouse_movements);

    uniform_camera_args get_args(float y_res, float fov) const;
};
} // namespace fractal
