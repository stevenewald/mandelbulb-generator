#pragma once
#include "shader.hpp"

namespace fractal {
class Program {
    Shader vertex_shader_;
    Shader fragment_shader_;
    const unsigned int SHADER_PROGRAM;

public:
    explicit Program(
        const std::filesystem::path& vertex_path,
        const std::filesystem::path& fragment_path
    );

    void use() const;

    int get_uniform_location(const char* name) const;
    int get_uniform_block_location(const char* name) const;

    unsigned int
    get_id() const
    {
        return SHADER_PROGRAM;
    }

    Program(const Program&) = delete;
    Program(Program&&) = delete;
    Program& operator=(const Program&) = delete;
    Program& operator=(Program&&) = delete;

    ~Program();
};
} // namespace fractal
