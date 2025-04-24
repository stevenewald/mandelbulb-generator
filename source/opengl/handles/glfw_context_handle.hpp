#pragma once

namespace fractal {
class GlfwContextHandle {
public:
    GlfwContextHandle();
    ~GlfwContextHandle();

    GlfwContextHandle(const GlfwContextHandle&) = delete;
    GlfwContextHandle(GlfwContextHandle&&) = delete;
    GlfwContextHandle& operator=(const GlfwContextHandle&) = delete;
    GlfwContextHandle& operator=(GlfwContextHandle&&) = delete;
};
} // namespace fractal
