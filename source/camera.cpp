#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

namespace fractal {
void
Camera::modify_yaw(float delta)
{
    yaw_ += delta;
}

void
Camera::modify_pitch(float delta)
{
    pitch_ += delta;
}

void
Camera::modify_radius(float delta)
{
    radius_ += delta;
    radius_ = std::min(radius_, MAX_RADIUS);
    radius_ = std::max(radius_, MIN_RADIUS);
}

bool
Camera::process_input(GLFWwindow* window)
{
    bool input_processed = false;
    float delta = DELTA;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        delta *= 10;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        input_processed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        modify_yaw(delta);
        input_processed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        modify_yaw(-delta);
        input_processed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        modify_pitch(-delta);
        input_processed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        modify_pitch(delta);
        input_processed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        modify_radius(-delta);
        input_processed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        modify_radius(delta);
        input_processed = true;
    }

    return input_processed;
}

bool
Camera::process_input(std::pair<float, float> mouse_movements)
{
    if (static_cast<int>(mouse_movements.first) == 0
        && static_cast<int>(mouse_movements.second) == 0)
        return false;
    modify_yaw(mouse_movements.first * .002f);
    modify_pitch(-mouse_movements.second * .003f);
    return true;
}

Camera::camera_args
Camera::get_args(float y_res, float fov) const
{
    Camera::camera_args args{};

    args.camera_position[0] = radius_ * cosf(pitch_) * sinf(yaw_);
    args.camera_position[1] = radius_ * sinf(pitch_);
    args.camera_position[2] = radius_ * cosf(pitch_) * cosf(yaw_);

    glm::vec3 target{};
    glm::vec3 camera_forward =
        glm::normalize(target - args.camera_position); // view direction
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    args.camera_right =
        glm::normalize(glm::cross(camera_forward, world_up));       // camera X
    args.camera_up = glm::cross(args.camera_right, camera_forward); // camera Y

    float fov_rads = glm::radians(fov);
    float z_plane = y_res / tanf(fov_rads * 0.5f);
    args.image_plane_center = z_plane * camera_forward;

    args.sun_direction = glm::normalize(glm::vec3{1, .1, .2});

    return args;
}
} // namespace fractal
