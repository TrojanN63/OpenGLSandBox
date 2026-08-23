#include "wall.hpp"
#include "gameObject.hpp"
using namespace std;
#include <string>
#include <GLFW/glfw3.h>

wall::wall()
  :object(
    "../assets/shaders/notNorm.vert",
    "../assets/shaders/texture.frag",
    "../assets/textures/wall.png",
    1.0f,
    1.0f
  )
{
};
void wall::step(GLFWwindow* window){
  object.Scale(64, 64);
  object.Position(100, 100);
  object.Rotation(0);
};
