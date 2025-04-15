#pragma once

namespace fractal {
class GlfwHandle {
public:
    GlfwHandle();
    ~GlfwHandle();

    GlfwHandle(const GlfwHandle&) = delete;
    GlfwHandle(GlfwHandle&&) = delete;
    GlfwHandle& operator=(const GlfwHandle&) = delete;
    GlfwHandle& operator=(GlfwHandle&&) = delete;
};
} // namespace fractal
