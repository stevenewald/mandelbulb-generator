#include "camera_ubo.hpp"

#include "camera.hpp"
#include "opengl_bindings.hpp"

namespace fractal {

CameraUBO::CameraUBO()
{
    glGenBuffers(1, &ubo_);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
    glBufferData(
        GL_UNIFORM_BUFFER, sizeof(Camera::camera_args), nullptr, GL_DYNAMIC_DRAW
    );
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

CameraUBO::~CameraUBO()
{
    glDeleteBuffers(1, &ubo_);
}

void
CameraUBO::update(const Camera::camera_args& args) const
{
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Camera::camera_args), &args);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void
CameraUBO::bind(unsigned int binding_point) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, ubo_);
}

} // namespace fractal
