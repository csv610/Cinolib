cmake_minimum_required(VERSION 3.10)
project(cinolib LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the cinolib directory for the configuration script
set(cinolib_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# --- Options ---
option(CINOLIB_BUILD_EXAMPLES "Build cinolib examples" ON)

# Modules options (mirrored from cinolib-config.cmake for visibility in CMake GUIs)
option(CINOLIB_USES_OPENGL_GLFW_IMGUI   "Use OpenGL, GLFW and ImGui" ON)
option(CINOLIB_USES_TETGEN              "Use Tetgen"                 ON)
option(CINOLIB_USES_TRIANGLE            "Use Triangle"               ON)
option(CINOLIB_USES_SHEWCHUK_PREDICATES "Use Shewchuk Predicates"    ON)
option(CINOLIB_USES_INDIRECT_PREDICATES "Use Indirect Predicates"    ON)
option(CINOLIB_USES_GRAPH_CUT           "Use Graph Cut"              OFF)
option(CINOLIB_USES_BOOST               "Use Boost"                  ON)
option(CINOLIB_USES_VTK                 "Use VTK"                    ON)
option(CINOLIB_USES_SPECTRA             "Use Spectra"                ON)
option(CINOLIB_USES_CGAL_GMP_MPFR       "Use CGAL, GMP and MPFR"     ON)

# --- Library Setup ---
# Include the existing cinolib-config.cmake which defines the 'cinolib' target and its dependencies
include(cinolib-config.cmake)

# --- Examples ---
if(CINOLIB_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# --- Testing ---
enable_testing()
add_subdirectory(tests)
