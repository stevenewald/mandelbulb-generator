include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND mandelbulb-generator_exe
    VERBATIM
)
add_dependencies(run-exe mandelbulb-generator_exe)

include(cmake/lint-targets.cmake)

add_folders(Project)
