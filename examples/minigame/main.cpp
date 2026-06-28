#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Shader.hpp>
#include<../../engine/Mesh.hpp>
#include<../../engine/Texture.hpp>
#include<../../engine/Input.hpp>
#include<../../engine/gameObject.hpp>

using namespace std;

int main(){
  if (!glfwInit()){ //iniciando glfw
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //configurando glfw
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "mago-dava");

  GLFWwindow* window = glfwCreateWindow(640, 640, "Games Dava Jonas", nullptr, nullptr); //criando e iniciando janela

  if (!window){
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window); //adicionando ao contexto

  int version = gladLoadGL(glfwGetProcAddress);

  if (version == 0){
    std::cerr << "Failed to initialize OpenGL context\n";
    return -1;
  }

  gameObject playa(
    "../assets/shaders/texture.vert",
    "../assets/shaders/texture.frag",
    "../assets/textures/playa.png",
    0.2f,
    0.2f
  );

  Input input; //inicializa o input

  float x = 0;
  float y = 1;

  float hspd = 0;
  float vspd = 0;
  
  int move = 0;
  
  float grvt = 0.01f;
  float jumpForce = 0.05f;
  float spd = 0.02f;

  bool left;
  bool right;
  bool jump;
  
  glEnable(GL_BLEND);

  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
  );
  while(!glfwWindowShouldClose(window)){ //loop principal enquanto está aberta a janela
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); //cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    playa.ShaderUse();

    playa.Scale(1.0f);
    playa.Rotation(0.0f);

    playa.Bind(0);

    //definindo inputs
    right = input.keyPressed(window, GLFW_KEY_D);
    left = input.keyPressed(window, GLFW_KEY_A);
    jump = input.keyPressed(window, GLFW_KEY_SPACE);

    move = right - left;

    hspd = move * spd;

    x+=hspd;

    if (jump && y<0.1) vspd+=jumpForce;

    if (y>0) vspd-=grvt;

    if (y+vspd < 0){
      if (y+(vspd/abs(vspd))/100 > 0){
        y-=0.01f;
      }
        y, vspd = 0, 0;
    }

    y+=vspd;

    playa.Position(x, y); //efetivamente mudando o transform

    playa.Draw(); //desenhando
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
