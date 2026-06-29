#include"Input.hpp"
#include<glad/gl.h>
#include<GLFW/glfw3.h>

Input::Input(){};

bool Input::keyPressed(GLFWwindow* window, int key){
  return glfwGetKey(window, key)==GLFW_PRESS;
};
void Input::mousePos(GLFWwindow* window, double &xpos, double &ypos){
  double mousexpos, mouseypos;
  int width, height;

  glfwGetCursorPos(window, &mousexpos, &mouseypos);
  glfwGetWindowSize(window, &width, &height);

  xpos = (mousexpos / width) * 2.0f - 1.0f;
  ypos = 1.0f - (mouseypos / height) * 2.0f;
};
bool Input::mouseButton(GLFWwindow* window, int button, int action){
  return glfwGetMouseButton(window, button)==(action);
};
