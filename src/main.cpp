#include <iostream>
//É importante fazer a exportação do glad antes do glfw
#include <glad/gl.h>
#include <GLFW/glfw3.h>

//definição dos vértices
float vertices[] = {
  0.0f, -0.5f, 0.0f,
  -0.5f, 0.5f, 0.0f,
  0.5f, 0.5f, 0.0f
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

void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
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
  GLFWwindow* window = glfwCreateWindow(800, 600, "Teste", nullptr, nullptr);

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

  //Buffers

  GLuint VAO;
  GLuint VBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(vertices),
    vertices,
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

  //Esse aqui é o loop principal que opera enquanto a janela estiver aberta
  while (!glfwWindowShouldClose(window)){
    glClearColor(
      0.1f,
      0.1f,
      0.2f,
      1.0f
    );

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    glDrawArrays(
      GL_TRIANGLES,
      0,
      3
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
