#pragma once
#include "../../engine/gameObject.hpp"
#include <string>
#include <GLFW/glfw3.h>
using namespace std;
class wall{
  public:
    gameObject object;
    wall();
    void step(GLFWwindow* window);
};
