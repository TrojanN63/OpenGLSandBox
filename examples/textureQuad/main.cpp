#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Shader.hpp>
#include<../../engine/Mesh.hpp>
#include<../../engine/Texture.hpp>

using namespace std;

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

  Texture hand("../assets/textures/hand.png");
  GLint offset = glGetUniformLocation(shader.ID, "offset");
  GLint scale = glGetUniformLocation(shader.ID, "scale");
  GLint angle = glGetUniformLocation(shader.ID, "angle");

  Mesh quad(vertices, indices);

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
  while((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL error: " << err << std::endl;
  }

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    shader.setInt("texture1", 0);

    hand.bind(0);

    float x = sin(glfwGetTime())*0.5f;
    float z = abs(sin(glfwGetTime()));
    float a = glfwGetTime();

    shader.setVec2("offset", x, 0);
    shader.setFloat("scale", z);
    shader.setFloat("angle", a);

    quad.draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
