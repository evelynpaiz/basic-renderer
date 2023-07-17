cmake_minimum_required(VERSION 3.16)

# Find source files
file(
    GLOB_RECURSE sources
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp src/*.h include/*.h
)

# Define the executable
add_executable(Sandbox ${sources})

# Define include directories
target_include_directories(
    Sandbox
    PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

# Link external libraries
target_link_libraries(Sandbox PRIVATE Renderer::Engine)

# Define the target properties
set_target_properties(Sandbox PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    XCODE_GENERATE_SCHEME TRUE
    XCODE_SCHEME_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

# Define solution tree organization
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${sources}
)