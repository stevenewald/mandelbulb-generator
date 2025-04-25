#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace fractal {
class Camera {
    static constexpr float DELTA = 0.001f;
    float radius_ = 4.0f;
    float pitch_ = 0.0001f;
    float yaw_;

public:
    explicit Camera(float start_yaw = 0.0f) : yaw_{start_yaw} {}

    void modify_yaw(float delta);
    void modify_pitch(float delta);
    void modify_radius(float delta);

    bool process_input(GLFWwindow* window);

    struct camera_args {
        alignas(16) glm::vec3 camera_position;
        alignas(16) glm::vec3 camera_right;
        alignas(16) glm::vec3 camera_up;
        alignas(16) glm::vec3 image_plane_center;
        alignas(16) glm::vec3 sun_direction;
    };

    camera_args get_args(float y_res, float fov) const;
};
} // namespace fractal
