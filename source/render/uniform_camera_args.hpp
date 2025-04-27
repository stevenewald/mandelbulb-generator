#pragma once
#include <glm/vec3.hpp>

namespace fractal {
// Meets alignment requirements to be directly passed as uniform
struct uniform_camera_args {
    alignas(16) glm::vec3 camera_position;
    alignas(16) glm::vec3 camera_right;
    alignas(16) glm::vec3 camera_up;
    alignas(16) glm::vec3 image_plane_center;
    alignas(16) glm::vec3 sun_direction;
};
} // namespace fractal
