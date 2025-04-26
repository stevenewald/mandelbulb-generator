#pragma once

#ifdef __EMSCRIPTEN__
#  include <GLES3/gl3.h>
#else
#  include <glad/glad.h>
#  include <GLFW/glfw3.h>
#endif
