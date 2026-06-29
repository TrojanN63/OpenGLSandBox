#pragma once
#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>

class Input{
  public:
    Input();

    bool keyPressed(GLFWwindow* window, int key);
    void mousePos(GLFWwindow* window, double &xpos, double &ypos);
    bool mouseButton(GLFWwindow* window, int button, int action=GLFW_PRESS);
};

