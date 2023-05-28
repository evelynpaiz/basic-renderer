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
set(GLM_UNINSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(3rdparty/glm)

## STB
add_library(stb INTERFACE)

target_include_directories(
    stb
    INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb/
)

add_library(stb::stb ALIAS stb)