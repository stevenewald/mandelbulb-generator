#include "app/engine.hpp"

namespace fractal {

Program
App::create_fractal_program(
    const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path
)
{
    unsigned int vao{};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return Program{vertex_path, fragment_path};
}

App::App()
{
    unsigned int vao{};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    program.use();
    initialize_uniforms_();
}

void
App::initialize_uniforms_()
{
    int vertex_skybox_location = program.get_uniform_location("skybox");
    glUniform1i(vertex_skybox_location, 0);
}

} // namespace fractal
