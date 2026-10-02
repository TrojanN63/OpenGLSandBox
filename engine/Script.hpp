#pragma once
#include <memory>
#include "Input.hpp"
#include <GLFW/glfw3.h>
class gameObject;

class Script {
  protected:
    gameObject* object;
  public:
    Script(gameObject* obj)
      : object(obj) {}
    virtual ~Script() = default;
    virtual void Step(GLFWwindow*, Input&) = 0;
};
