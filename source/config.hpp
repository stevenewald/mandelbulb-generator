#pragma once

#include <array>

namespace fractal {
constexpr float START_YAW = 90.0f;
constexpr unsigned int WIDTH = 1000;
constexpr unsigned int HEIGHT = 750;
constexpr float FOV = 70.0f;
constexpr std::array<const char*, 6> CUBEMAP_IMAGES{"images/px.png", "images/nx.png",
                                                    "images/py.png", "images/ny.png",
                                                    "images/pz.png", "images/nz.png"};
constexpr const char* VERTEX_PATH{"shaders/vertex/single_triangle.glsl"};
constexpr const char* FRAGMENT_PATH{"shaders/fragment/mandelbulb.glsl"};

} // namespace fractal
