cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    mandelbulb-generator
    VERSION 0.1.0
	DESCRIPTION "Mandelbulb Raymarcher"
    HOMEPAGE_URL "https://stevenewald.com/"
    LANGUAGES CXX
)

if(EMSCRIPTEN)
  message(STATUS "Configuring for Emscripten / WebAssembly")
endif()

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

set(BUILD_SHARED_LIBS OFF)

add_compile_definitions(GLFW_INCLUDE_NONE)

# ---- Declare library ----


add_library(
    mandelbulb-generator_lib OBJECT
    source/lib.cpp
	source/handles/glfw_context_handle.cpp
	source/handles/shader.cpp
	source/handles/program.cpp
	source/camera.cpp
	source/camera_ubo.cpp
	source/handles/cubemap.cpp
	source/handles/image.cpp
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

if(NOT EMSCRIPTEN)
  # glfw - opengl
  find_package(glfw3 REQUIRED)
  target_link_libraries(mandelbulb-generator_lib PRIVATE glfw)

  # glad - exposes function pointers to opengl functions
  find_package(glad REQUIRED)
  target_link_libraries(mandelbulb-generator_lib PRIVATE glad::glad)
else()
  # Emscripten bundles its own GLFW/WebGL2 port
endif()

# stb - image loading
find_package(stb REQUIRED)
target_link_libraries(mandelbulb-generator_lib PRIVATE stb::stb)

# glm - math
find_package(glm REQUIRED)
target_link_libraries(mandelbulb-generator_lib PRIVATE glm::glm)


# ---- Declare executable ----

add_executable(mandelbulb-generator_exe source/main.cpp)
add_executable(mandelbulb-generator::exe ALIAS mandelbulb-generator_exe)

set_property(TARGET mandelbulb-generator_exe PROPERTY OUTPUT_NAME mandelbulb-generator)

target_compile_features(mandelbulb-generator_exe PRIVATE cxx_std_20)

target_link_libraries(mandelbulb-generator_exe PRIVATE mandelbulb-generator_lib)

if(EMSCRIPTEN)
	set_target_properties(mandelbulb-generator_exe PROPERTIES SUFFIX ".html")
	target_link_options(mandelbulb-generator_exe PRIVATE
    # JavaScript port of GLFW3
    "-sUSE_GLFW=3"
	"--embed-file=${CMAKE_SOURCE_DIR}/shaders/fragment/mandelbulb_es.glsl@/shaders/fragment/mandelbulb_es.glsl"
    "--embed-file=${CMAKE_SOURCE_DIR}/shaders/vertex/single_triangle_es.glsl@/shaders/vertex/single_triangle_es.glsl"
    "--embed-file=${CMAKE_SOURCE_DIR}/images/@/images"
    # WebGL2 / ES3 support
    "-sMAX_WEBGL_VERSION=2"
    "-sMIN_WEBGL_VERSION=2"
    # Embind & modularize
    "-lembind"
    # "-sMODULARIZE=1"
    "-sASSERTIONS=1"
	"-sEXCEPTION_CATCHING_ALLOWED=[..]"
  )
endif()

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
