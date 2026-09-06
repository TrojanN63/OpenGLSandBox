#include"Input.hpp"
#include<glad/gl.h>
#include<GLFW/glfw3.h>

Input::Input(GLFWwindow* window){
  glfwSetScrollCallback(window, Input::scroll_callback);
}

double Input::scroll_y = 0.0;
double Input::scroll_x = 0.0;

bool Input::keyPressed(GLFWwindow* window, int key, int action){
  return glfwGetKey(window, key)==action;
};
void Input::mousePos(GLFWwindow* window, double &xpos, double &ypos){
  glfwGetCursorPos(window, &xpos, &ypos);
};
bool Input::mouseButton(GLFWwindow* window, int button, int action){
  return glfwGetMouseButton(window, button)==(action);
};
void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  scroll_y = yoffset;
  scroll_x = xoffset;
}
void Input::scroll_update(){
  scroll_y = 0.0;
  scroll_x = 0.0;
}
