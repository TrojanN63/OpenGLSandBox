#pragma once
#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>

class Input{
  public:
    Input();

    bool keyPressed(GLFWwindow* window, int key);
};

