cmake_minimum_required(VERSION 3.20)

project(OpenGLSandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

# GLAD
add_library(glad STATIC
    external/src/gl.c
)

target_include_directories(glad PUBLIC
    external/include
)

# ENGINE
file(GLOB ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp"
)

add_library(engine STATIC
    ${ENGINE_SOURCES}
)

target_include_directories(engine PUBLIC
  external/include
  engine
  include
)

target_link_libraries(engine PUBLIC
  glad
  glfw
)

# JOGOS
add_executable(Minigame
  examples/minigame/main.cpp
)

target_include_directories(Minigame PRIVATE
    external/include
)

target_link_libraries(Minigame PRIVATE
  engine
)

add_executable(HotlineNatal
  examples/hotlineNatal/main.cpp
)

target_include_directories(HotlineNatal PRIVATE
    external/include
)

target_link_libraries(HotlineNatal PRIVATE
  engine
)

if (MINGW)
    target_link_options(HotlineNatal PRIVATE
        -static-libgcc
        -static-libstdc++
    )
endif()
