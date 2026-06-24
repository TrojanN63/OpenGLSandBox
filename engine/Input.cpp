#include"Input.hpp"
#include<glad/gl.h>
#include<GLFW/glfw3.h>

Input::Input(){};

bool Input::keyPressed(GLFWwindow* window, int key){
  return glfwGetKey(window, key)==GLFW_PRESS;
};
