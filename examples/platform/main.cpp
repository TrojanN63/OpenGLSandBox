#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<vector>
#include<../../engine/Input.hpp>
#include<../../engine/gameObject.hpp>
#include<../../engine/Render.hpp>
#include<../../engine/Script.hpp>

using namespace std;

int main(){
  if (!glfwInit()){
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "Platform");

  GLFWwindow* window = glfwCreateWindow(640, 480, "Platform Testing Objects", nullptr, nullptr);

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

  Render renderer(window);

  Input input(window);

  class PlayerScript : public Script {
    public:
      PlayerScript(gameObject* obj)
        : Script(obj) {}

      float x = 320;
      float y = 240;

      float hspd = 0;
      float vspd = 0;

      int move = 0;

      float grvt = 1.0f;
      float jumpForce = 15.0f;
      float spd = 5.0f;

      bool left;
      bool right;
      bool jump;


    void Step(GLFWwindow* window, Input& input) override {
      right = input.keyPressed(window, GLFW_KEY_D);
      left = input.keyPressed(window, GLFW_KEY_A);
      jump = input.keyPressed(window, GLFW_KEY_SPACE);

      move = right - left;

      hspd = move * spd;

      x+=hspd;

      if (jump && y>=240) vspd-=jumpForce;

      if (y<240) vspd+=grvt;

      if (y+vspd > 240){
        if (y+(vspd/abs(vspd)) <= 240){
          y+=1.0f;
        }
        y, vspd = 0, 0;
      }

      y+=vspd;

      object->Position(x,y);
    }
  };
 
  vector<unique_ptr<gameObject>> liveObjects;
  liveObjects.push_back(
    make_unique<gameObject>(
      "../assets/shaders/notNorm.vert",
      "../assets/shaders/texture.frag",
      "../assets/textures/playa.png",
      64,
      64,
      320,
      240
    )
  );

  gameObject* player = liveObjects[0].get();
  
  player->SetScript(
    make_unique<PlayerScript>(player)
  );
  
  glEnable(GL_BLEND);

  glBlendFunc(
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA
  );
  while(!glfwWindowShouldClose(window)){
    renderer.setBgColor(0.1f, 0.1f, 0.1f, 1.0f);
    renderer.beginFrame();

    for (auto& object : liveObjects){
      renderer.draw(*object);
      object->Rotation(0);
      object->Scale(1,-1);
      object->Step(window, input);
    }

    renderer.endFrame();
  }

  return 0;
}
