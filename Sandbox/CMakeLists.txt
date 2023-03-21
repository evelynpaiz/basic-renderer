cmake_minimum_required(VERSION 3.10)

# Find source files
file(GLOB sources src/*.cpp src/*.h include/*.h)

# Define the executable
add_executable(Sandbox ${sources})

# Define headers for the target
target_include_directories(
    Sandbox
    PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

# Link external libraries
target_link_libraries(Sandbox PRIVATE BR::Engine)

# Define solution tree organization
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${sources}
)