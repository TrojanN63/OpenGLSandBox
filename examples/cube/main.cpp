#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include "../../engine/Shader.hpp"
#include<../../engine/Mesh.hpp>

using namespace std;

vector<float> vertices = {
  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f,
  0.5f,  0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,

  -0.5f, -0.5f, 0.5f,
  0.5f, -0.5f, 0.5f,
  0.5f,  0.5f, 0.5f,
  -0.5f,  0.5f, 0.5f
};

vector<unsigned int> indices = {
  0, 1, 3,
  1, 2, 3,

  4, 5, 7,
  5, 6, 7,

  1, 2, 5,
  2, 5, 6,

  2, 3, 7,
  2, 6, 7,

  0, 1, 4,
  1, 4, 5,

  0, 3, 4,
  3, 4, 7
};

int main(){
  if (!glfwInit()){
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(640, 640, "Cubo", nullptr, nullptr);

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

  glEnable(GL_DEPTH_TEST);

  Shader shader(
    "../assets/shaders/basic.vert",
    "../assets/shaders/basic.frag"
  );

  shader.use();

  shader.setVec3(
    "objectColor",
    1.0f,
    0.0f,
    1.0f
  );

  Mesh quad(vertices, indices);

  quad.addAttribute(
    0,
    3,
    3 * sizeof(float),
    0
  );

  quad.finish();
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(
      GL_COLOR_BUFFER_BIT |
      GL_DEPTH_BUFFER_BIT
    );

    shader.use();

    shader.setFloat("angle", glfwGetTime());
    
    quad.draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
