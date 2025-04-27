#pragma once

#include <GLFW/glfw3.h>
#ifdef __EMSCRIPTEN__
#  include <GLES3/gl3.h>
#else
#  include <glad/glad.h>
#endif
