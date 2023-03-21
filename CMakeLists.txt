# CMake C++ features
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
include_directories(3rdparty/include)

# Required libraries
find_package(OpenGL REQUIRED)

# Third party libraries
## GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(3rdparty/glfw)

## GLEW
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS ON CACHE BOOL "" FORCE)

add_subdirectory(3rdparty/glew)

# Own libraries and executables
add_subdirectory(Engine)
add_subdirectory(Sandbox)

# Define solution tree organization
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${sources} ${public_headers}
)