#include"Input.hpp"
#include<glad/gl.h>
#include<GLFW/glfw3.h>

char Input::command = '\0';

Input::Input(
){
};

void Input::callback(GLFWwindow* window, unsigned int codepoint){
  Input::command = static_cast<char>(codepoint);
};

void Input::setcallback(GLFWwindow* window){
  glfwSetCharCallback(window, callback);
};
