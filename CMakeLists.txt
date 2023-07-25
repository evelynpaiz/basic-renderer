# CMake C++ features
cmake_minimum_required(VERSION 3.16)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 20)

# Definition of the solution
project(basic-renderer)

# Target directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Use folders for solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Third party libraries
find_package(OpenGL REQUIRED)
include(Dependencies.cmake)

# Define options for the user
option(RENDERER_BUILD_EXAMPLES "Build the sandbox (example) executable" ON)

# Own libraries and executables
add_subdirectory(Resources)
add_subdirectory(Engine)

if (RENDERER_BUILD_EXAMPLES)
    add_subdirectory(Sandbox)
endif()
