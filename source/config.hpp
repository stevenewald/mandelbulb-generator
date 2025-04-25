#pragma once

#include <array>

namespace fractal {
constexpr float START_YAW = 90.0f;
constexpr unsigned int WIDTH = 800;
constexpr unsigned int HEIGHT = 600;
constexpr float WIDTH_F = static_cast<float>(WIDTH);
constexpr float HEIGHT_F = static_cast<float>(HEIGHT);
constexpr float FOV = 60.0f;
constexpr std::array<const char*, 6> CUBEMAP_IMAGES{"images/px.png", "images/nx.png",
                                                    "images/py.png", "images/ny.png",
                                                    "images/pz.png", "images/nz.png"};
#ifdef __EMSCRIPTEN__
constexpr const char* VERTEX_PATH{"shaders/vertex/single_triangle_es.glsl"};
constexpr const char* FRAGMENT_PATH{"shaders/fragment/mandelbulb_es.glsl"};
#else
constexpr const char* VERTEX_PATH{"shaders/vertex/single_triangle_core.glsl"};
constexpr const char* FRAGMENT_PATH{"shaders/fragment/mandelbulb_core.glsl"};
#endif

} // namespace fractal
