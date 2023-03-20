# CMake version and C++ features
cmake_minimum_required(VERSION 3.10)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 20)

# Definition of the solution
project(basic-renderer)

# Target directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Use folders for solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Define include directories
include_directories(/usr/local/include)
include_directories(3rdparty/include)

# Define libraries directories
link_directories(/usr/local/lib)

# Required libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Solution project(s)
add_subdirectory(Engine)