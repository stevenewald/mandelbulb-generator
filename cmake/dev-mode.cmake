include(cmake/folders.cmake)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()

add_custom_target(
    run-exe
    COMMAND mandelbulb-generator_exe
    VERBATIM
)
add_dependencies(run-exe mandelbulb-generator_exe)

include(cmake/lint-targets.cmake)

add_folders(Project)
