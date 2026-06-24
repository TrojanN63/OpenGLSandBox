#include"Input.hpp"
#include<glad/gl.h>
#include<GLFW/glfw3.h>

Input::Input(){
}
void Input::callback(GLFWwindow* window, unsigned int codepoint){
  std::cout << static_cast<char>(codepoint) << std::endl;
};
void Input::setcallback(GLFWwindow* window){
  glfwSetCharCallback(window, callback);
};
