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
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "hln");

  GLFWwindow* window = glfwCreateWindow(640, 640, "Hotline Natal", nullptr, nullptr);

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

  gameObject xdemon(
    "../assets/shaders/texture.vert",
    "../assets/shaders/texture.frag",
    "../assets/textures/xdemon/idle.png",
    0.2f,
    0.2f
  );

  Input input;

  float x = 0;
  float y = 0;
  float angle = 0;

  float hspd = 0;
  float vspd = 0;
  
  int movex = 0;
  int movey = 0;

  float spd = 0.02f;

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

  double punchTime;

  vector<string> frames = {
    "../assets/textures/xdemon/punch0.png",
    "../assets/textures/xdemon/punch1.png",
    "../assets/textures/xdemon/idle.png"
  };
  int frame = 0;
  bool animation = false;
  double frameDur = 0.05;

  float xsize = 1.0f;
  float ysize = 1.0f;

  glEnable(GL_BLEND);

  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
  );
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
    movey = up - down;

    float deltax = mousex - x;
    float deltay = mousey - y;

    angle = atan2(deltay, deltax);

    hspd = movex * spd;
    vspd = movey * spd;

    time = glfwGetTime();

    y+=vspd;
    x+=hspd;

    if (punch and canpunch){
      xsize*=-1;
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
          frame=0;
          animation=false;
        }else{
          frame++;
        }
        punchTime = time;
      }
    }

    xdemon.Position(x, y);
    xdemon.Rotation((angle-2*atan(1))*xsize);
    xdemon.Scale(xsize, ysize);

    xdemon.Draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
