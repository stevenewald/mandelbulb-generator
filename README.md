# Mandelbulb Raymarcher

A real-time Mandelbulb renderer using OpenGL fragment shader ray marching. Built with GLFW, GLAD, and ImGui.

---

## Work In Progress

- [x] GLFW window and OpenGL context
- [x] GLAD function loader
- [ ] Basic fragment shader setup
- [ ] Raymarching loop (distance estimator, normal, shading)
- [ ] ImGui UI for live controls (zoom, power, steps, color)
- [ ] Orbiting camera with mouse input
- [ ] Screenshot/export feature
- [ ] Code cleanup and modularization

---

## Features (planned)

- Real-time GPU Mandelbulb rendering
- Smooth orbital camera controls
- Interactive tweaking with ImGui
- Adjustable iteration depth, epsilon, lighting
- High-resolution frame output

---

## [Conan](https://conan.io/)-installed Dependencies

- [GLFW](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [Dear ImGui](https://github.com/ocornut/imgui)
---

## Build Instructions

```bash
git clone https://github.com/stevenewald/mandelbulb-raymarcher.git
cd mandelbulb-raymarcher
conan install . -s build_type=Release -b missing
cmake --preset=ci-ubuntu -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j
./build/mandelbulb-raymarcher

