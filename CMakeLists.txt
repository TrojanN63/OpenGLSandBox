cmake_minimum_required(VERSION 3.20)

project(OpenGLSandbox)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)

#[[
add_executable(PolygonGenerator
   examples/polygonGenerator/main.cpp
   engine/FileUtils.cpp
   engine/Shader.cpp
   external/src/gl.c
)

add_executable(TextureQuad
    examples/textureQuad/main.cpp
    engine/FileUtils.cpp
    engine/Shader.cpp
    engine/stb_image.cpp
    engine/Mesh.cpp
    engine/Texture.cpp
    engine/Input.cpp
    external/src/gl.c
)

]]

add_executable(Minigame.exe
  examples/minigame/main.cpp
    engine/FileUtils.cpp
    engine/Shader.cpp
    engine/stb_image.cpp
    engine/Mesh.cpp
    engine/Texture.cpp
    engine/Input.cpp
    engine/gameObject.cpp
    external/src/gl.c
)

#[[

add_executable(Cube
  examples/cube/main.cpp
    engine/FileUtils.cpp
    engine/Shader.cpp
    engine/Mesh.cpp
    external/src/gl.c
)



target_include_directories(PolygonGenerator PRIVATE
    external/include
)

target_link_libraries(PolygonGenerator PRIVATE
    glfw
)

target_include_directories(TextureQuad PRIVATE
    external/include
)

target_link_libraries(TextureQuad PRIVATE
    glfw
)
]]

target_include_directories(Minigame.exe PRIVATE
    external/include
)

target_link_libraries(Minigame.exe PRIVATE
    glfw
)

#[[
target_include_directories(Cube PRIVATE
    external/include
)

target_link_libraries(Cube PRIVATE
    glfw
)
]]
