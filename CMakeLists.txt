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
include(Dependencies.cmake)

find_package(OpenGL REQUIRED)

# Own libraries and executables
add_subdirectory(Engine)
add_subdirectory(Sandbox)