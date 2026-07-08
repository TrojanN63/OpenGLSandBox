#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Input.hpp>
#include<../../engine/gameObject.hpp>

using namespace std;

int main(){
  if (!glfwInit()){
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "HotlineNatal");

  GLFWwindow* window = glfwCreateWindow(640, 480, "Hotline Natal", nullptr, nullptr);

  if (!window){
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);

  if (version == 0){
    std::cerr << "Failed to initialize OpenGL context\n";
    return -1;
  }

  gameObject wall(
    "../assets/shaders/notNorm.vert",
    "../assets/shaders/texture.frag",
    "../assets/textures/wall.png",
    1.0f,
    1.0f
  );
  gameObject xdemon(
    "../assets/shaders/notNorm.vert",
    "../assets/shaders/texture.frag",
    "../assets/textures/xdemon/idle.png",
    1.0f,
    1.0f
  );

  wall.SetProjection(640, 480);
  xdemon.SetProjection(640, 480);

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

  glEnable(GL_BLEND);

  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
  );
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    wall.ShaderUse();
    wall.Bind(0);

    wall.Position(wallx,wally);
    wall.Scale(64,64);
    wall.Rotation(0);

    wall.Draw();

    xdemon.ShaderUse();

    xdemon.Bind(0);

    right = input.keyPressed(window, GLFW_KEY_D);
    left = input.keyPressed(window, GLFW_KEY_A);
    up = input.keyPressed(window, GLFW_KEY_W);
    down = input.keyPressed(window, GLFW_KEY_S);
    punch = input.mouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    releasePunch = input.mouseButton(window, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE);

    input.mousePos(window, mousex, mousey);
    
    movex = right - left;
    movey = down - up;

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
      xdemon.UpdateTex(frames.at(frame), 0);
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

    xdemon.Scale(xsize, ysize);
    xdemon.Position(x, y);
    xdemon.Rotation(angle-2*atan(1));

    xdemon.Draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
