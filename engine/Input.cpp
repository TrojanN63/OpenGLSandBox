#include"Input.hpp"
#include<glad/gl.h>
#include<GLFW/glfw3.h>

Input::Input(){};

bool Input::keyPressed(GLFWwindow* window, int key){
  return glfwGetKey(window, key)==GLFW_PRESS;
};
void Input::mousePos(GLFWwindow* window, double &xpos, double &ypos){
  glfwGetCursorPos(window, &xpos, &ypos);
};
bool Input::mouseButton(GLFWwindow* window, int button, int action){
  return glfwGetMouseButton(window, button)==(action);
};
