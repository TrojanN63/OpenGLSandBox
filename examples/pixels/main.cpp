#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Input.hpp>
#include<../../engine/gameObject.hpp>

using namespace std;

int main(){
  if (!glfwInit()){
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "ExpRend");

  GLFWwindow* window = glfwCreateWindow(640, 480, "Experimental Rendering", nullptr, nullptr);

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

  gameObject wall(
    "../assets/shaders/notNorm.vert",
    "../assets/shaders/texture.frag",
    "../assets/textures/playa.png",
    1.0f,
    1.0f
  );

  wall.SetProjection(640, 480);
  
  glEnable(GL_BLEND);

  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
  );

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    wall.ShaderUse();
    wall.Bind(0);

    wall.Position(200,100);

    wall.Scale(128,128);

    float angle = glfwGetTime();
    wall.Rotation(angle);

    wall.Draw();
 
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
