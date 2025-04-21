#pragma once

#include "camera.hpp"
#include "program.hpp"

#include <glm/glm.hpp>

namespace fractal {

class CameraUBO {
public:
    struct CameraData {
        alignas(16) glm::vec3 campos;
        alignas(16) glm::vec3 right;
        alignas(16) glm::vec3 up;
        alignas(16) glm::vec3 z;
    };

    CameraUBO();
    ~CameraUBO();

    void update(const Camera::ray_args& args);
    void bind(GLuint bindingPoint = 0) const;
    void attachToShader(
        const Program& program, const std::string& blockName, GLuint bindingPoint = 0
    ) const;

private:
    GLuint ubo_;
};

} // namespace fractal
