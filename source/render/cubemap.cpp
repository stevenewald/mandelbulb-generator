#include "render/cubemap.hpp"

#include "opengl_bindings.hpp"
#include "render/image.hpp"

#include <fmt/format.h>

namespace fractal {

namespace {
unsigned int
create_texture()
{
    unsigned int texture_id{};
    glGenTextures(1, &texture_id);
    return texture_id;
}
} // namespace

Cubemap::Cubemap(std::span<const char* const, 6> face_filepaths) :
    TEXTURE_ID{create_texture()}
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, TEXTURE_ID);
    glActiveTexture(GL_TEXTURE0);

    for (unsigned int i = 0; i < face_filepaths.size(); i++) {
        Image image{face_filepaths[i]};
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.get_width(),
            image.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.get_data()
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Cubemap::~Cubemap()
{
    glDeleteTextures(1, &TEXTURE_ID);
}
} // namespace fractal
