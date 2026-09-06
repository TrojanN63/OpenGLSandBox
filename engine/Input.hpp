#pragma once
#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>

class Input{
  public:
    Input(GLFWwindow* window);

    bool keyPressed(GLFWwindow* window, int key, int action);
    void mousePos(GLFWwindow* window, double &xpos, double &ypos);
    bool mouseButton(GLFWwindow* window, int button, int action=GLFW_PRESS);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    static double scroll_y;
    static double scroll_x;

    static void scroll_update();
};

