#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Shader.hpp>
#include<../../engine/Mesh.hpp>
#include<../../engine/Texture.hpp>
#include<../../engine/Input.hpp>

using namespace std;

vector<float> vertices = { //definição de vértices
  -0.1f, 0.1f, 0.0f, 0.0f, 1.0f,
  -0.1f, -0.1f, 0.0f, 0.0f, 0.0f,
  0.1f, 0.1f, 0.0f, 1.0f, 1.0f,
  0.1f, -0.1f ,0.0f, 1.0f, 0.0f
};

vector<unsigned int> indices = { //definição de índices que formas os triângulos
  0, 1, 3,
  0, 3, 2
};

int main(){
  if (!glfwInit()){ //iniciando glfw
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //configurando glfw
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

  Shader shader( //lendo os shaders
    "../assets/shaders/texture.vert",
    "../assets/shaders/texture.frag"
  );

  Texture playa("../assets/textures/playa.png"); //lendo a textura
  GLint offset = glGetUniformLocation(shader.ID, "offset"); //pegando as variáveis do transform
  GLint scale = glGetUniformLocation(shader.ID, "scale");
  GLint angle = glGetUniformLocation(shader.ID, "angle");

  Mesh quad(vertices, indices); //formando a malha

  quad.addAttribute(
    0,
    3,
    5 * sizeof(float),
    0
  );
  quad.addAttribute(
    1,
    2,
    5 * sizeof(float),
    3 * sizeof(float)
  );
  
  quad.finish();
  
  GLenum err;

  Input input;
  input.setcallback(window);

  while((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL error: " << err << std::endl;
  }

  float x = 0;
  float hspd = 0;
  int move = 0;

  while(!glfwWindowShouldClose(window)){ //loop principal enquanto está aberta a janela
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); //cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use(); //usando shader
    //shader.setVec2("offset", 0.0f, 0.0f);
    shader.setFloat("scale", 1.0f);
    shader.setFloat("angle", 0.0f);
    shader.setInt("texture1", 0); //usando texture

    playa.bind(0);
    
    float spd = 0.02f;

    if (input.command=='a') {
      move=-1;
    }else if (input.command=='d'){
      move=1;
    }else{
      move=0;
    }

    hspd = move * spd;

    x+=hspd;

    shader.setVec2("offset", x, 0); //efetivamente mudando o transform

    quad.draw(); //desenhando
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
