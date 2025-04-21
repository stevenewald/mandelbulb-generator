#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>

namespace fractal {
unsigned int
loadCubemap(std::vector<std::string> faces);
} // namespace fractal
