cmake_minimum_required(VERSION 3.10)

# Find source files
file(
    GLOB_RECURSE sources
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp
)

# Find header files
file(
    GLOB_RECURSE public_headers
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    include/*.h
)

# Define the library
add_executable(Engine ${sources} ${public_headers})

# Link external libraries
target_link_libraries(Engine OpenGL::GL glfw GLEW)

# Define headers
target_include_directories(
    Engine
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

# Define the target properties
set_target_properties(Engine PROPERTIES 
    PUBLIC_HEADER "${public_headers}"
)

# Define solution tree organization
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${sources} ${shaders} ${public_headers}
)