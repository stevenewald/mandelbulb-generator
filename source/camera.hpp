#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>

namespace fractal {
class Camera {
    float radius_ = 3.0f;
    float pitch_ = 0.0001f;
    float yaw_ = 0.0f;

public:
    void modify_yaw(float delta);
    void modify_pitch(float delta);
    void modify_radius(float delta);

    bool process_input(GLFWwindow* window);

    struct ray_args {
        glm::vec3 campos;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 z;
        glm::vec3 sunDirection;
    };

    ray_args get_args(float y_res) const;
};
} // namespace fractal
