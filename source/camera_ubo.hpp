#pragma once

#include "camera.hpp"

#include <glm/glm.hpp>

namespace fractal {

class CameraUBO {
public:
    struct camera_data {
        alignas(16) glm::vec3 campos;
        alignas(16) glm::vec3 right;
        alignas(16) glm::vec3 up;
        alignas(16) glm::vec3 z;
        alignas(16) glm::vec3 sun_direction;
    };

    CameraUBO();
    CameraUBO(const CameraUBO&) = delete;
    CameraUBO(CameraUBO&&) = delete;
    CameraUBO& operator=(const CameraUBO&) = delete;
    CameraUBO& operator=(CameraUBO&&) = delete;
    ~CameraUBO();

    void update(const Camera::ray_args& args) const;
    void bind(unsigned int binding_point = 0) const;

private:
    unsigned int ubo_{};
};

} // namespace fractal
