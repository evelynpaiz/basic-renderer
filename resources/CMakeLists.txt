cmake_minimum_required(VERSION 3.16)

# Define the resources
file(GLOB_RECURSE shaders RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} shaders/*.glsl)
file(GLOB_RECURSE common RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} common/*)

file(GLOB_RECURSE textures RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} textures/*)
file(GLOB_RECURSE models RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} models/*)

set(resources ${shaders} ${common} ${textures} ${models})

set(outputs)
foreach (resource ${resources})
    string(REPLACE "/" "_" name ${resource})
    set(input ${CMAKE_CURRENT_SOURCE_DIR}/${resource})
    set(output ${CMAKE_BINARY_DIR}/Resources/${resource})
    add_custom_command(
        OUTPUT ${output}
        DEPENDS ${input}
        COMMAND ${CMAKE_COMMAND} -E copy ${input} ${output}
    )
    list(APPEND outputs ${output})
endforeach()

# Define the resources
add_library(Resources INTERFACE ${resources} ${outputs})
add_library(Renderer::Resources ALIAS Resources)

# Define solution tree organization
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${resources}
)

# Exclude files from ${CMAKE_BINARY_DIR}/Resources/
source_group(""
    FILES ${outputs}
    REGULAR_EXPRESSION "^Resources/.*" 
)
