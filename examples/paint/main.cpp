#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Input.hpp>
#include<../../engine/gameObject.hpp>
#include<../../engine/Render.hpp>

using namespace std;

int main(){
  if (!glfwInit()){
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "paint");

  GLFWwindow* window = glfwCreateWindow(640, 480, "Super Torj Paint", nullptr, nullptr);

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

  Input input;

  vector<gameObject> liveObjects = {};

  glEnable(GL_BLEND);

  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
  );
  while(!glfwWindowShouldClose(window)){
    renderer.beginFrame();

    
    for (int i=0; i<liveObjects.size(); i++){
      if (liveObjects.at(i).live){
        liveObjects.at(i).Position(100,100);
        liveObjects.at(i).Rotation(0.0f);
        liveObjects.at(i).Scale(1.0f,1.0f);
        renderer.draw(liveObjects.at(i));
      }
    }

    if (input.keyPressed(window, GLFW_KEY_E)){

      gameObject block(
        "../assets/shaders/notNorm.vert",
        "../assets/shaders/texture.frag",
        "../assets/textures/wall.png",
        64,
        64
      );
      liveObjects.push_back(block);
    }
    if (input.keyPressed(window, GLFW_KEY_D)){
      liveObjects = {};
    }

    renderer.endFrame();
  }

  return 0;
}
