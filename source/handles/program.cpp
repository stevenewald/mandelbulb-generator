#include "handles/program.hpp"

#include "opengl_bindings.hpp"

#include <fmt/format.h>

#include <array>
#include <filesystem>
#include <stdexcept>

namespace fractal {
namespace {
void
check_link_error(unsigned int program_id)
{
    int success{};
    std::array<char, 512> info_log{};
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        glGetProgramInfoLog(program_id, 512, nullptr, info_log.data());
        throw std::runtime_error(
            fmt::format("ERROR::PROGRAM::LINKING_FAILED {}", info_log.data())
        );
    }
}
} // namespace

Program::Program(
    const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path
) :
    vertex_shader_{create_shader(vertex_path, ShaderType::vertex)},
    fragment_shader_{create_shader(fragment_path, ShaderType::fragment)},
    SHADER_PROGRAM{glCreateProgram()}
{
    glAttachShader(SHADER_PROGRAM, vertex_shader_.get_id());
    glAttachShader(SHADER_PROGRAM, fragment_shader_.get_id());
    glBindAttribLocation(SHADER_PROGRAM, 0, "dummy");
    glLinkProgram(SHADER_PROGRAM);
    check_link_error(SHADER_PROGRAM);
}

void
Program::use() const
{
    glUseProgram(SHADER_PROGRAM);
}

unsigned int
Program::get_uniform_block_location(const char* name) const
{
    unsigned int index = glGetUniformBlockIndex(SHADER_PROGRAM, name);
    if (index == GL_INVALID_OPERATION) {
        throw std::runtime_error(fmt::format("Unable to find block index {}", name));
    }
    return index;
}

int
Program::get_uniform_location(const char* name) const
{
    int index = glGetUniformLocation(SHADER_PROGRAM, name);
    if (index == GL_INVALID_VALUE) {
        throw std::runtime_error(fmt::format("Unable to find block index {}", name));
    }
    return index;
}

Program::~Program()
{
    glDeleteProgram(SHADER_PROGRAM);
}
} // namespace fractal
