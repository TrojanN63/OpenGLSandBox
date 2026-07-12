#pragma once
#include "../../engine/gameObject.hpp"
#include <string>
#include "../../engine/Input.hpp"
#include <GLFW/glfw3.h>
using namespace std;
class player{
  public:
  Input input;

  float x = 320;
  float y = 240;
  float angle = 0;

  float hspd = 0;
  float vspd = 0;
  
  int movex = 0;
  int movey = 0;

  float spd = 10.0f;

  bool left;
  bool right;
  bool up;
  bool down;
  bool punch;
  bool releasePunch;
  bool canpunch = true;

  double mousex;
  double mousey;

  double time;
  double execTime=0;

  double punchTime;

  vector<string> frames = {
    "../assets/textures/xdemon/punch0.png",
    "../assets/textures/xdemon/punch1.png",
    "../assets/textures/xdemon/idle.png"
  };
  int frame = 0;
  bool animation = false;
  double frameDur = 0.05;

  float xsize = 128;
  float ysize = 128;

  float wallx = 100;
  float wally = 100;
    gameObject object;
    player();
    void step(GLFWwindow* window);
};
