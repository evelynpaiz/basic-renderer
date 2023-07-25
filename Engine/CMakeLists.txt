cmake_minimum_required(VERSION 3.16)

# Find source files
file(
    GLOB_RECURSE sources
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp src/*.h
)

# Find header files
file(
    GLOB_RECURSE public_headers
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    include/*.h
)

# Find all resources
file(
    GLOB_RECURSE resources
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    resources/*
)

set(outputs)
foreach (resource ${resources})
    string(REPLACE "/" "_" name ${resource})
    set(input ${CMAKE_CURRENT_SOURCE_DIR}/${resource})
    set(output ${CMAKE_BINARY_DIR}/${resource})
    add_custom_command(
        OUTPUT ${output}
        DEPENDS ${input}
        COMMAND ${CMAKE_COMMAND} -E copy ${input} ${output}
    )
    list(APPEND outputs ${output})
endforeach()

# Define the engine library
add_library(Engine STATIC ${sources} ${public_headers})
add_library(Renderer::Engine ALIAS Engine)

# Define the include directories for this target
target_include_directories(
    Engine
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

# Define properties for the target
set_target_properties(Engine PROPERTIES 
    PUBLIC_HEADER "${public_headers}"
)

# Link external libraries
target_link_libraries(Engine 
    Renderer::Resources spdlog::spdlog OpenGL::GL glfw::glfw glew::glew glm::glm stb::stb assimp::assimp imgui::imgui
)

# Define pre-compiled header
target_precompile_headers(Engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/enginepch.h)

# Define solution tree organization
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${public_headers} ${sources}
)
