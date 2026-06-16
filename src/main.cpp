#include <iostream>
//É importante fazer a exportação do glad antes do glfw
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

using namespace std;

bool commandMode = false;
string commandBuffer;
int newN = 10;
bool needUpdate = false;
bool wireChange = false;
bool Wire = false;
float colorR;
float colorG;
float colorB;
bool hexChange = false;
float offset = 0;

//Obtendo o valor de pi
const double pi = 4 * atan(1);

//Callback dos caracteres
void character_callback(GLFWwindow* window, unsigned int codepoint){
  if (static_cast<char>(codepoint)==':'){
    commandMode = true;
    commandBuffer.clear();
  }
  if (commandMode){
    if (static_cast<char>(codepoint)!=':'){
      commandBuffer+=static_cast<char>(codepoint);
    }
  }
}
//Callback das teclas especiais
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action != GLFW_PRESS)
        return;

    if (!commandMode)
        return;

    if (key == GLFW_KEY_BACKSPACE)
    {
        if (!commandBuffer.empty())
            commandBuffer.pop_back();
    }

  if (key == GLFW_KEY_ENTER){
    if (commandBuffer.at(0)=='n'){
        commandBuffer.erase(0,1);
        newN = stoi(commandBuffer);

        needUpdate = true;
    }
    if (commandBuffer.at(0)=='w'){
      Wire = !Wire;
      wireChange = true;
    }
    if (commandBuffer.at(0)=='c'){
      commandBuffer.erase(0,1);
      colorR = stoi(commandBuffer.substr(0,2), nullptr, 16);
      colorG = stoi(commandBuffer.substr(2,2), nullptr, 16);
      colorB = stoi(commandBuffer.substr(4,2), nullptr, 16);
      hexChange = true; 
    }
    if (commandBuffer.at(0)=='r'){
      commandBuffer.erase(0,1);
      offset += stof(commandBuffer)*pi;
      needUpdate = true;
    }
    commandMode = false;
  }
}
//definição dos vértices
float vertices[] = {
  -0.25f, 0.43f, 0.0f,
  0.25f, 0.43f, 0.0f,
  0.0f, 0.0f, 0.0f,
  -0.5f, 0.0f, 0.0f,
  -0.25f, -0.43f, 0.0f,
  0.25f, -0.43f, 0.0f,
  0.5f, 0.0f, 0.0f,
};

//Agora vem os índices para fazer o EBO, onde eu vou economizar vértice
unsigned int indices[] = {
  0, 1, 2,
  0, 2, 3,
  2, 3, 4,
  2, 4, 5,
  2, 5, 6,
  1, 2, 6
};

//Vértices e índices do círculo aproximado, inicialmente só com o centro
vector<float> verticesCircle = {
    0.0f, 0.0f, 0.0f,
};
vector<int> indicesCircle = {};

float angle = offset;
int i = 0;

void setVerticesOfCircle(int n){
  while(i<=n){
    i += 1;
    angle += (2*pi)/n;
    float pcos = cos(angle)/2;
    float psin = sin(angle)/2;

    verticesCircle.push_back(pcos);
    verticesCircle.push_back(psin);
    verticesCircle.push_back(0.0f);

    indicesCircle.push_back(0);
    indicesCircle.push_back(i);
    if (i==n){
      indicesCircle.push_back(1);
    }else{
      indicesCircle.push_back(i+1);
    }
  }
  cout << "Vertices: " << verticesCircle.size() / 3 << endl;
  cout << "Indices: " << indicesCircle.size() << endl;
};

//Shaders, eles são escritos em uma linguagem própria
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;

void main()
{
    FragColor = vec4(objectColor, 1.0);
}
)";

int main(){
  //Isso inicia o glfw
  if (!glfwInit()){
    return -1;
  }

  //Configuração do OpenGL?
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //Aqui criamos a janela, passando a resolução, nome da janela e nulo para variáveis que não sei o que são
  GLFWwindow* window = glfwCreateWindow(640, 640, "OpenGL Sandbox", nullptr, nullptr);

  //Isso para o glfw em caso da janela fechar
  if (!window){
    glfwTerminate();
    return -1;
  }

  //Isso faz da janela o contexto atual
  glfwMakeContextCurrent(window);

  //Inicializa o GLAD
  int version = gladLoadGL(glfwGetProcAddress);

  if (version == 0){
    std::cerr << "Failed to initialize OpenGL context\n";
    return -1;
  }

  //Isso é só um teste, onde ele tenta pegar os dados do hardware para ver o que suporta
  std::cout << "Vendor: "
            << glGetString(GL_VENDOR)
            << '\n';

  std::cout << "Renderer: "
            << glGetString(GL_RENDERER)
            << '\n';

  std::cout << "Version: "
            << glGetString(GL_VERSION)
            << '\n';

  //Aqui ele cria os shaders de fato

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(
    vertexShader,
    1,
    &vertexShaderSource,
    nullptr
  );

  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(
    fragmentShader,
    1,
    &fragmentShaderSource,
    nullptr
  );

  glCompileShader(fragmentShader);

  GLuint shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);

  //Linkando a cor
  GLint colorLocation = glGetUniformLocation(shaderProgram, "objectColor");

  //Cores
  glUseProgram(shaderProgram);
  
  glUniform3f(
    colorLocation,
    1,
    1,
    1
  );
  //Buffers

  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
  setVerticesOfCircle(10);

  glBufferData(
    GL_ARRAY_BUFFER,
    verticesCircle.size() * sizeof(float),
    verticesCircle.data(),
    GL_STATIC_DRAW
  );

  //Aqui entra a configuração do EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indicesCircle.size() * sizeof(int),
    indicesCircle.data(),
    GL_STATIC_DRAW
  );

  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    3 * sizeof(float),
    (void*)0
  );

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //Leitura dos dados
  glfwSetCharCallback(window, character_callback);
  //Teclas especiais
  glfwSetKeyCallback(window, key_callback);
  //Esse aqui é o loop principal que opera enquanto a janela estiver aberta
  while (!glfwWindowShouldClose(window)){
    //Atualização
    if (commandMode){
      string title = ":" + commandBuffer;
      glfwSetWindowTitle(window, title.c_str());
    }else{
      string title = "OpenGL Sandbox";
      glfwSetWindowTitle(window, title.c_str());
    }

    if (hexChange){
      glUniform3f(
        colorLocation,
        colorR/255,
        colorG/255,
        colorB/255
      );
      hexChange = false;
    }

    if (needUpdate){
      verticesCircle.clear();
      verticesCircle.push_back(0.0f);
      verticesCircle.push_back(0.0f);
      verticesCircle.push_back(0.0f);
      indicesCircle.clear();

      angle = offset;
      i = 0;

      setVerticesOfCircle(newN);

      glBindBuffer(GL_ARRAY_BUFFER, VBO);

      glBufferData(
        GL_ARRAY_BUFFER,
        verticesCircle.size() * sizeof(float),
        verticesCircle.data(),
        GL_STATIC_DRAW
      );
      
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

      glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indicesCircle.size() * sizeof(int),
        indicesCircle.data(),
        GL_STATIC_DRAW
      );

      needUpdate = false;
    }
    if (wireChange){
      if (Wire){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
      }
      wireChange = false;
    }

    glClearColor(
      0.0f,
      0.0f,
      0.0f,
      1.0f
    );

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    glDrawElements(
      GL_TRIANGLES,
      indicesCircle.size(),
      GL_UNSIGNED_INT,
      0
    );

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  //Limpando os buffers
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glDeleteProgram(shaderProgram);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
