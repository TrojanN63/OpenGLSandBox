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
    void Step() override {
      cout << "funcionando";
    }
  };
 
  vector<unique_ptr<gameObject>> liveObjects;
  liveObjects.push_back(
    make_unique<gameObject>(
      "../assets/shaders/notNorm.vert",
      "../assets/shaders/texture.frag",
      "../assets/textures/xdemon/idle.png",
      128,
      128,
      50,
      50
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
      object->Scale(1,1);
      object->Step();
    }

    renderer.endFrame();
  }

  return 0;
}
