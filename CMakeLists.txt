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

# Required libraries
find_package(OpenGL REQUIRED)

# Third party libraries
## SPDLOG
set(SPDLOG_BUILD_ONLY_HEADERS ON CACHE BOOL "" FORCE)

add_subdirectory(3rdparty/spdlog)
add_library(spdlog::spdlog ALIAS spdlog_header_only)

## GLFW
set(GLFW_MAPPING OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(3rdparty/glfw)
add_library(glfw::glfw ALIAS glfw)

set_target_properties(glfw PROPERTIES FOLDER "")

## GLEW
set(GLEW_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(GLEW_INSTALL OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS ON CACHE BOOL "" FORCE)

add_subdirectory(3rdparty/glew)
add_library(glew::glew ALIAS glew)

## GLM
add_subdirectory(3rdparty/glm)

## STB
add_library(stb::stb INTERFACE IMPORTED)
target_include_directories(
    stb::stb
    INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb/
)

# Own libraries and executables
add_subdirectory(Engine)
add_subdirectory(Sandbox)