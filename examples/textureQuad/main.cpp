#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Shader.hpp>
#include<stb/stb_image.h>
#include<../../engine/Mesh.hpp>

using namespace std;

//agora eu vou usar x, y, z e também u e v, que representam as coordenadas da textura.

vector<float> vertices = {
  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
  0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
  0.5f, -0.5f ,0.0f, 1.0f, 0.0f
};

vector<unsigned int> indices = {
  0, 1, 3,
  0, 3, 2
};

int main(){
  if (!glfwInit()){
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(256, 256, "Render", nullptr, nullptr);

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

  Shader shader(
    "../assets/shaders/texture.vert",
    "../assets/shaders/texture.frag"
  );

  GLuint texture;
  GLuint offset = glGetUniformLocation(shader.ID, "offset");
  GLuint scale = glGetUniformLocation(shader.ID, "scale");
  GLuint angle = glGetUniformLocation(shader.ID, "angle");

  glGenTextures(1, &texture);

  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_WRAP_S,
    GL_REPEAT
  );

  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_WRAP_T,
    GL_REPEAT
  );
  
  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MIN_FILTER,
    GL_NEAREST_MIPMAP_NEAREST
  );

  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MAG_FILTER,
    GL_NEAREST_MIPMAP_NEAREST
  );

  int width;
  int height;
  int channels;

  Mesh quad(vertices, indices);

  GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load("../assets/textures/hand.png", &width, &height, &channels, 0);

  if (!data) {
    std::cout << "Falha ao carregar textura\n";
  }

  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    5 * sizeof(float),
    (void*)0
  );
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    5*sizeof(float),
    (void*)(3*sizeof(float))
  );
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  std::cout << "channels: " << channels << std::endl;
  std::cout << "width: " << width << " height: " << height << std::endl;
  
  GLenum err;
  while((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL error: " << err << std::endl;
  }

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    shader.setInt("texture1", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(
      GL_TEXTURE_2D,
      texture
    );

    float x = sin(glfwGetTime())*0.5f;
    float z = abs(sin(glfwGetTime()));
    float a = glfwGetTime();
    glUniform2f(
      offset,
      x+0.3f,
      0.0f
    );
    glUniform1f(
      scale,
      z
    );
    glUniform1f(
      angle,
      a
    );

    quad.draw(6);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
