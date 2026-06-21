cmake_minimum_required(VERSION 3.20)

project(OpenGLSandbox)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)

add_executable(OpenGLSandbox
    examples/polygonGenerator/main.cpp
    engine/FileUtils.cpp
    engine/Shader.cpp
    external/src/gl.c
)

target_include_directories(OpenGLSandbox PRIVATE
    external/include
)

target_link_libraries(OpenGLSandbox PRIVATE
    glfw
)
