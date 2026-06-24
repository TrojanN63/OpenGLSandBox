#pragma once
#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>

class Input{
  public:
    Input();

    static void callback(GLFWwindow* window, unsigned int codepoint);

    void setcallback(GLFWwindow* window);
};

