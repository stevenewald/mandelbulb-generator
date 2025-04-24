#pragma once

#include <fmt/format.h>
#include <glad/glad.h>

#include <cstdint>

#include <filesystem>

namespace fractal {
enum class ShaderType : std::uint8_t { vertex, fragment };

class Shader {
    const unsigned int SHADER_ID;

public:
    unsigned int get_id() const;

    Shader(const char* str, ShaderType type);

    Shader(const Shader&) = delete;
    Shader(Shader&&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&) = delete;

    ~Shader();
};

Shader create_shader(const std::filesystem::path& path, ShaderType type);
} // namespace fractal
