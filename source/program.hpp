#pragma once
#include "shader.hpp"

#include <glad/glad.h>

#include <array>
#include <filesystem>
#include <span>

namespace fractal {
void
check_link_error(unsigned int program_id)
{
    int success{};
    std::array<char, 512> info_log{};
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        glGetShaderInfoLog(program_id, 512, nullptr, info_log.data());
        throw std::runtime_error(
            fmt::format("ERROR::PROGRAM::LINKING_FAILED {}", info_log.data())
        );
    }
}

class Program {
    Shader vertex_shader_;
    Shader fragment_shader_;
    const unsigned int SHADER_PROGRAM;

public:
    explicit Program(
        const std::filesystem::path& vertex_path,
        const std::filesystem::path& fragment_path
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
    use() const
    {
        glUseProgram(SHADER_PROGRAM);
    }

    int
    get_uniform_location(const char* name) const
    {
        return glGetUniformLocation(SHADER_PROGRAM, name);
    }

    Program(const Program&) = delete;
    Program(Program&&) = delete;
    Program& operator=(const Program&) = delete;
    Program& operator=(Program&&) = delete;

    ~Program() { glDeleteProgram(SHADER_PROGRAM); }
};
} // namespace fractal
