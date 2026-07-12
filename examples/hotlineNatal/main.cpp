#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Input.hpp>
#include<../../engine/gameObject.hpp>
#include<../../engine/Render.hpp>
#include "player.hpp"

using namespace std;

int main(){
  if (!glfwInit()){
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "HotlineNatal");

  GLFWwindow* window = glfwCreateWindow(640, 480, "Hotline Natal", nullptr, nullptr);

  if (!window){
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);

  if (version == 0){
    std::cerr << "Failed to initialize OpenGL context\n";
    return -1;
  }

  Render renderer(window);

  gameObject wall(
    "../assets/shaders/notNorm.vert",
    "../assets/shaders/texture.frag",
    "../assets/textures/wall.png",
    1.0f,
    1.0f
  );
  player xdemon;

  float wallx = 100;
  float wally = 100;

  glEnable(GL_BLEND);

  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
  );
  while(!glfwWindowShouldClose(window)){
    renderer.beginFrame();

    wall.Position(wallx,wally);
    wall.Scale(64,64);
    wall.Rotation(0);

    renderer.draw(wall);

    xdemon.step(window);

    renderer.draw(xdemon.object);

    renderer.endFrame();
  }

  return 0;
}
