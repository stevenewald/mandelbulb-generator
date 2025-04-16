#include "lib.hpp"

#include "glfw_handle.hpp"

#include <fmt/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <string>

library::library() : name{fmt::format("{}", "mandelbulb-generator")} {}

void
run()
{
    fractal::GlfwHandle handle;

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "GL Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Initialize ImGui context and style
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup ImGui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Use ImDrawList to draw text directly onto the screen.
        // Coordinates are in pixels from the top-left corner.
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        // Draw text at position (20, 20) with white color.
        draw_list->AddText(
            ImVec2(20, 20), IM_COL32(255, 255, 255, 255), "Hello, ImGui!"
        );

        // Finalize the ImGui frame.
        ImGui::Render();

        // Clear the screen with a red background.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the ImGui draw data (which now includes the direct text).
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers to display the rendered frame.
        glfwSwapBuffers(window);
    }

    // Cleanup ImGui and GLFW resources.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
}
