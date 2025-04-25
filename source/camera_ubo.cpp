#include "camera_ubo.hpp"

#include <glad/glad.h>

namespace fractal {

CameraUBO::CameraUBO()
{
    glGenBuffers(1, &ubo_);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(camera_data), nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

CameraUBO::~CameraUBO()
{
    glDeleteBuffers(1, &ubo_);
}

void
CameraUBO::update(const Camera::ray_args& args) const
{
    camera_data data{args.campos, args.right, args.up, args.z, args.sun_direction};

    glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(camera_data), &data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void
CameraUBO::bind(unsigned int binding_point) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, ubo_);
}

} // namespace fractal
