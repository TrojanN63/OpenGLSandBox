#pragma once

#include "gameObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Render{
  public:
    Render(GLFWwindow* window);

    void beginFrame();
    void endFrame();
    void draw(gameObject& object);

  private:
    GLFWwindow* window;
    glm::mat4 projection;
};
