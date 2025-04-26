#include "lib.hpp"

#include "config.hpp"
#include "initialization.hpp"

#include <fmt/core.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <thread>

namespace fractal {
namespace {
const std::unique_ptr<app> APP = std::make_unique<app>();
} // namespace

void
setup()
{
    APP->program.use();
    initialize_uniforms(APP->program);
}

void
tick()
{
    static bool has_run = false;
    glfwPollEvents();
    APP->glfw_window.on_first();
    if (!APP->camera.process_input(APP->glfw_window.get_window()) && has_run) {
        return;
    }
    has_run = true;

    APP->camera_ubo.update(APP->camera.get_args(APP->glfw_window.get_width(), FOV));
    APP->camera_ubo.bind();

    int vertex_res_location = APP->program.get_uniform_location("resolution");
    glUniform2f(
        vertex_res_location, APP->glfw_window.get_width(), APP->glfw_window.get_height()
    );

    // Clear the screen with a red background.
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap buffers to display the rendered frame.
    glfwSwapBuffers(APP->glfw_window.get_window());
}

void
run_forever()
{
    while (!glfwWindowShouldClose(APP->glfw_window.get_window())) {
        tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
} // namespace fractal
