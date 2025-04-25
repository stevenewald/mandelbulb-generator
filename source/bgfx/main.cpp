// main.cpp
#define GLFW_EXPOSE_NATIVE_X11
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h> // for glfwGetX11Display / glfwGetX11Window

#include <iostream>

int
main()
{
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "bgfx on Linux", nullptr, nullptr);
    if (!window)
        return -1;

    // Linux (X11) only:
    bgfx::PlatformData pd{};
#if defined(_WIN32)
    pd.nwh = glfwGetWin32Window(window);
#elif defined(__linux__)
    pd.ndt = glfwGetX11Display();
    pd.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#else
    // add other platforms
#endif

    bgfx::Init init;
    init.type = bgfx::RendererType::Count;
    init.platformData = pd;
    init.resolution.width = 800;
    init.resolution.height = 600;
    if (!bgfx::init(init))
        return -1;

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFF0000ff, 1.0f, 1);
    bgfx::setViewRect(0, 0, 0, 800, 600);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        bgfx::touch(0);
        bgfx::frame();
    }

    bgfx::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
