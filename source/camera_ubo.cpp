#include "camera_ubo.hpp"

#include <glad/glad.h>

namespace fractal {

CameraUBO::CameraUBO()
{
    glGenBuffers(1, &ubo_);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraData), nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

CameraUBO::~CameraUBO()
{
    glDeleteBuffers(1, &ubo_);
}

void
CameraUBO::update(const Camera::ray_args& args)
{
    CameraData data = {args.campos, args.right, args.up, args.z, args.sunDirection};

    glBindBuffer(GL_UNIFORM_BUFFER, ubo_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraData), &data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void
CameraUBO::bind(GLuint bindingPoint) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ubo_);
}

void
CameraUBO::attachToShader(
    const Program& program, const std::string& blockName, GLuint bindingPoint
) const
{
    GLuint blockIndex = program.get_uniform_block_location(blockName.c_str());
    glUniformBlockBinding(program.get_id(), blockIndex, bindingPoint);
}
} // namespace fractal
