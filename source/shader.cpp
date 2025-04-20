#include "shader.hpp"

#include <fmt/format.h>
#include <glad/glad.h>

#include <cstdint>

#include <array>
#include <expected>
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace fractal {

namespace {

void
check_compilation_error(unsigned int shader_id)
{
    int success{};
    std::array<char, 512> info_log{};
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        glGetShaderInfoLog(shader_id, 512, nullptr, info_log.data());
        throw std::runtime_error(fmt::format(
            "ERROR::SHADER::VERTEX::COMPILATION_FAILED: {}", info_log.data()
        ));
    }
}

unsigned int
compile_shader(const char* shader_code, ShaderType type)
{
    unsigned int shader{};
    switch (type) {
        case ShaderType::vertex:
            shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::fragment:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            throw std::invalid_argument("Unknown shader type");
    }

    glShaderSource(shader, 1, &shader_code, nullptr);
    glCompileShader(shader);

    check_compilation_error(shader);

    return shader;
}
} // namespace

Shader
create_shader(const std::filesystem::path& path, ShaderType type)
{
    std::ifstream in_str{path, std::ios::binary};
    const std::string in_str_c{std::istreambuf_iterator<char>(in_str), {}};
    return {in_str_c.data(), type};
}

Shader::Shader(const char* str, ShaderType type) : SHADER_ID{compile_shader(str, type)}
{}

unsigned int
Shader::get_id() const
{
    return SHADER_ID;
}

Shader::~Shader()
{
    glDeleteShader(SHADER_ID);
}
} // namespace fractal
