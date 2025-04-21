#include "program.hpp"

#include <glad/glad.h>

#include <array>
#include <filesystem>
#include <span>

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
    glLinkProgram(SHADER_PROGRAM);
    check_link_error(SHADER_PROGRAM);
}

void
Program::use() const
{
    glUseProgram(SHADER_PROGRAM);
}

int
Program::get_uniform_location(const char* name) const
{
    return glGetUniformLocation(SHADER_PROGRAM, name);
}

Program::~Program()
{
    glDeleteProgram(SHADER_PROGRAM);
}
} // namespace fractal
