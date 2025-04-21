#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
}

Camera::ray_args
Camera::get_args(float y_res) const
{
    glm::vec3 camPos{};
    camPos.x = radius_ * cosf(pitch_) * sinf(yaw_);
    camPos.y = radius_ * sinf(pitch_);
    camPos.z = radius_ * cosf(pitch_) * cosf(yaw_);

    glm::vec3 target = glm::vec3(0.0f);
    glm::vec3 forward = glm::normalize(target - camPos); // view direction
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp)); // camera X
    glm::vec3 up = glm::cross(right, forward);                      // camera Y

    float fov = glm::radians(60.0f);
    float zPlane = y_res / tan(fov * 0.5f);
    glm::vec3 z = zPlane * forward;
    return {camPos, right, up, z};
}
} // namespace fractal
