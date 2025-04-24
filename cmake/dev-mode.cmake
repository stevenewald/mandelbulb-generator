include(cmake/folders.cmake)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()

add_custom_target(
    run-opengl-exe
    COMMAND mandelbulb-generator-opengl_exe
    VERBATIM
)

add_custom_target(
    run-bgfx-exe
    COMMAND mandelbulb-generator-opengl_exe
    VERBATIM
)
add_dependencies(run-opengl-exe mandelbulb-generator-opengl_exe)
add_dependencies(run-bgfx-exe mandelbulb-generator-bgfx_exe)

include(cmake/lint-targets.cmake)

add_folders(Project)
