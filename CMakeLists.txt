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

# ---- Declare library ----


add_library(
    mandelbulb-generator_lib OBJECT
    source/lib.cpp
	source/handles/glfw_context_handle.cpp
	source/util.cpp
	source/shader.cpp
	source/program.cpp
	source/camera.cpp
	source/camera_ubo.cpp
)

target_include_directories(
    mandelbulb-generator_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(mandelbulb-generator_lib PUBLIC cxx_std_20)

# fmt - text formatting
find_package(fmt REQUIRED)
target_link_libraries(mandelbulb-generator_lib PRIVATE fmt::fmt)

# glfw - opengl
find_package(glfw3 REQUIRED)
target_link_libraries(mandelbulb-generator_lib PRIVATE glfw)

# glm - math
find_package(glm REQUIRED)
target_link_libraries(mandelbulb-generator_lib PRIVATE glm::glm)

# glad - exposes function pointers to opengl functions
find_package(glad REQUIRED)
target_link_libraries(mandelbulb-generator_lib PRIVATE glad::glad)

# ---- Imgui Bindings ----
add_library(
	imgui-bindings_lib
	bindings/imgui_impl_glfw.cpp
	bindings/imgui_impl_opengl3.cpp
)

target_include_directories(
    imgui-bindings_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bindings>"
)

find_package(imgui REQUIRED)
target_link_libraries(imgui-bindings_lib PUBLIC imgui::imgui)
target_link_libraries(imgui-bindings_lib PRIVATE glfw)

target_link_libraries(mandelbulb-generator_lib PRIVATE imgui-bindings_lib)


# ---- Declare executable ----

add_executable(mandelbulb-generator_exe source/main.cpp)
add_executable(mandelbulb-generator::exe ALIAS mandelbulb-generator_exe)

set_property(TARGET mandelbulb-generator_exe PROPERTY OUTPUT_NAME mandelbulb-generator)

target_compile_features(mandelbulb-generator_exe PRIVATE cxx_std_20)

target_link_libraries(mandelbulb-generator_exe PRIVATE mandelbulb-generator_lib)

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
