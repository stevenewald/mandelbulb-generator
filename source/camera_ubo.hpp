#pragma once

#include "camera.hpp"

#include <glm/glm.hpp>

namespace fractal {

class CameraUBO {
    unsigned int ubo_{};

public:
    CameraUBO();
    CameraUBO(const CameraUBO&) = delete;
    CameraUBO(CameraUBO&&) = delete;
    CameraUBO& operator=(const CameraUBO&) = delete;
    CameraUBO& operator=(CameraUBO&&) = delete;
    ~CameraUBO();

    void update(const Camera::camera_args& args) const;
    void bind(unsigned int binding_point = 0) const;
};

} // namespace fractal
