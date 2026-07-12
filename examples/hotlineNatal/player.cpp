#include "player.hpp"
#include "gameObject.hpp"
using namespace std;
#include <string>
#include <GLFW/glfw3.h>

player::player()
  :object(
    "../assets/shaders/notNorm.vert",
    "../assets/shaders/texture.frag",
    "../assets/textures/xdemon/idle.png",
    1.0f,
    1.0f
  )
{
};
void player::step(GLFWwindow* window){
  bool right = input.keyPressed(window, GLFW_KEY_D);
  bool left = input.keyPressed(window, GLFW_KEY_A);
  bool up = input.keyPressed(window, GLFW_KEY_W);
  bool down = input.keyPressed(window, GLFW_KEY_S);
  bool punch = input.mouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  bool releasePunch = input.mouseButton(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE);

  input.mousePos(window, mousex, mousey);

  int movex = right - left;
  int movey = down - up;

  float deltax = mousex - x;
  float deltay = mousey - y;

  angle = atan2(deltay, deltax);

  hspd = movex * spd;
  vspd = movey * spd;

  if (movex!=0 and movey!=0){
    hspd=movex*spd/sqrt(2);
    vspd=movey*spd/sqrt(2);
  }

  time = glfwGetTime();
 
  if (x<wallx){
    if (x+16+hspd>wallx-32 and y>wally-48 and y<wally+48){
      if (x+16+hspd/abs(hspd) < wallx-32){
        x+=hspd/abs(hspd);
      }
      hspd = 0,0;
    }
  }
  if (x>wallx){
    if (x-16+hspd<wallx+32 and y>wally-48 and y<wally+48){
      if (x-16+hspd/abs(hspd) > wallx+32){
        x+=hspd/abs(hspd);
      }
      hspd = 0,0;
    }
  }

  if (y<wally){
    if (y+16+vspd>wally-32 and x>wallx-48 and x<wallx+48){
      if (y+16+vspd/abs(vspd) < wally-32){
        y+=vspd/abs(vspd);
      }
      vspd = 0,0;
    }
  }
  if (y>wally){
    if (y-16+vspd<wally+32 and x>wallx-48 and x<wallx+48){
      if (y-16+vspd/abs(vspd) > wally+32){
        y+=vspd/abs(vspd);
      }
      vspd = 0,0;
    }
  }

  if (time-execTime >= 0.016){
    x+=hspd;
    y+=vspd;
    execTime=time;
  }

  if (punch and canpunch){
    animation = true;
    punchTime = time;
    canpunch = false;
  }
  if (releasePunch){
    canpunch = true;
  }

  if (animation){
    object.UpdateTex(frames.at(frame), 0);
    if (time - punchTime >= frameDur){
      if (frame==frames.size()-1){
        xsize*=-1;
        frame=0;
        animation=false;
      }else{
        frame++;
      }
      punchTime = time;
    }
  }

  object.Scale(xsize, ysize);
  object.Position(x, y);
  object.Rotation(angle-2*atan(1));
};
