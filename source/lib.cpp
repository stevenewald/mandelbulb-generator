#include "lib.hpp"

#include "camera.hpp"
#include "camera_ubo.hpp"
#include "config.hpp"
#include "cubemap.hpp"
#include "handles/glfw_context_handle.hpp"
#include "handles/glfw_window_handle.hpp"
#include "initialization.hpp"
#include "triangle.hpp"

#include <fmt/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>

namespace fractal {

void
run()
{
    app app{};

    app.program.use();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    loadCubemap({"px.png", "nx.png", "py.png", "ny.png", "pz.png", "nz.png"});
    initialize_uniforms(app.program);

    bool fst = true;

    // Main loop
    while (!glfwWindowShouldClose(app.glfw_window.get())) {
        glfwPollEvents();

        if (!app.camera.process_input(app.glfw_window.get()) && !fst) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        fst = false;

        app.camera_ubo.update(app.camera.get_args(HEIGHT));
        app.camera_ubo.bind();

        // Clear the screen with a red background.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers to display the rendered frame.
        glfwSwapBuffers(app.glfw_window.get());
    }
}
} // namespace fractal
