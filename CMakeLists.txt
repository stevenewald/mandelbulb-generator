cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    mandelbulb-generator
    VERSION 0.1.0
	DESCRIPTION "Mandelbulb Raymarcher"
    HOMEPAGE_URL "https://stevenewald.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

set(BUILD_SHARED_LIBS OFF)

add_compile_definitions(GLFW_INCLUDE_NONE)

# ---- Declare OpenGL library ----


add_library(
    mandelbulb-generator-opengl_lib OBJECT
    source/opengl/lib.cpp
	source/opengl/handles/glfw_context_handle.cpp
	source/opengl/util.cpp
	source/opengl/shader.cpp
	source/opengl/program.cpp
	source/opengl/camera.cpp
	source/opengl/camera_ubo.cpp
	source/opengl/cubemap.cpp
)

target_include_directories(
    mandelbulb-generator-opengl_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source/opengl>"
)

target_compile_features(mandelbulb-generator-opengl_lib PUBLIC cxx_std_20)

# fmt - text formatting
find_package(fmt REQUIRED)
target_link_libraries(mandelbulb-generator-opengl_lib PRIVATE fmt::fmt)

# glfw - opengl
find_package(glfw3 REQUIRED)
target_link_libraries(mandelbulb-generator-opengl_lib PRIVATE glfw)

# stb - image loading
find_package(stb REQUIRED)
target_link_libraries(mandelbulb-generator-opengl_lib PRIVATE stb::stb)

# glm - math
find_package(glm REQUIRED)
target_link_libraries(mandelbulb-generator-opengl_lib PRIVATE glm::glm)

# glad - exposes function pointers to opengl functions
find_package(glad REQUIRED)
target_link_libraries(mandelbulb-generator-opengl_lib PRIVATE glad::glad)

# ---- Declare OpenGL executable ----

add_executable(mandelbulb-generator-opengl_exe source/opengl/main.cpp)
add_executable(mandelbulb-generator-opengl::exe ALIAS mandelbulb-generator-opengl_exe)

set_property(TARGET mandelbulb-generator-opengl_exe PROPERTY OUTPUT_NAME mandelbulb-generator-opengl)

target_compile_features(mandelbulb-generator-opengl_exe PRIVATE cxx_std_20)

target_link_libraries(mandelbulb-generator-opengl_exe PRIVATE mandelbulb-generator-opengl_lib)

# ---- Declare BGFX library ----


add_library(
    mandelbulb-generator-bgfx_lib OBJECT
    source/bgfx/lib.cpp
)

target_include_directories(
    mandelbulb-generator-bgfx_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source/bgfx>"
)

target_compile_features(mandelbulb-generator-bgfx_lib PUBLIC cxx_std_20)

# bgfx - cross-platform graphics api
find_package(bgfx REQUIRED)
target_link_libraries(mandelbulb-generator-bgfx_lib PRIVATE bgfx::bgfx)

# ---- Declare BGFX executable ----

add_executable(mandelbulb-generator-bgfx_exe source/bgfx/main.cpp)
add_executable(mandelbulb-generator-bgfx::exe ALIAS mandelbulb-generator-bgfx_exe)

set_property(TARGET mandelbulb-generator-bgfx_exe PROPERTY OUTPUT_NAME mandelbulb-generator-bgfx)

target_compile_features(mandelbulb-generator-bgfx_exe PRIVATE cxx_std_20)
target_link_libraries(mandelbulb-generator-bgfx_exe PRIVATE bgfx::bgfx)
target_link_libraries(mandelbulb-generator-bgfx_exe PRIVATE glfw)

target_link_libraries(mandelbulb-generator-bgfx_exe PRIVATE mandelbulb-generator-bgfx_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT mandelbulb-generator_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of mandelbulb-generator"
  )
endif()

include(cmake/dev-mode.cmake)
