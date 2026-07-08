#include "Render.hpp"
#include "gameObject.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

Render::Render(
  GLFWwindow* window
)
  : window(window)
{
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  projection = glm::ortho(
    0.0f,
    (float)width,
    (float)height,
    0.0f
  );
};
void Render::beginFrame(){
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
};
void Render::endFrame(){
  glfwSwapBuffers(window);
  glfwPollEvents();
};
void Render::draw(gameObject& object){
  object.shader.use();

  object.shader.setMat4(
    "projection",
    projection
  );

  object.shader.setMat4(
    "model",
    object.GetModelMatrix()
  );

  object.sprite.bind(0);

  object.mesh.draw();
};
