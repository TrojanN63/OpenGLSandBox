#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include "gameObject.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include <vector>
#include <iostream>

gameObject::gameObject(
  //Transform transform,
  const std::string& vert,
  const std::string& frag,
  const std::string& spritePath,
  float sizex,
  float sizey
)
  : shader(vert, frag),
    mesh(sizex, sizey),
    sprite(spritePath)
{

  mesh.addAttribute(
    0,
    3,
    5 * sizeof(float),
    0
  );
  mesh.addAttribute(
    1,
    2,
    5 * sizeof(float),
    3 * sizeof(float)
  );

  mesh.finish();

  shader.use();
  shader.setInt("texture1", 0);

  GLenum err;

  while((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL error: " << err << std::endl;
  }
 
};
void gameObject::Position(
    float x,
    float y
){
  transform.position = {x,y};
};
void gameObject::Draw(){
  glm::mat4 model(1.0f);

  model = glm::translate(
    model,
    glm::vec3(
      transform.position,
      0.0f
    )
  );

  model = glm::rotate(
    model,
    transform.rotation,
    glm::vec3(0,0,1)
  );

  model = glm::scale(
    model,
    glm::vec3(
      transform.scale,
      1.0f
    )
  );

  shader.use();
  shader.setMat4("model", model);

  sprite.bind(0);
  mesh.draw();
};
void gameObject::Rotation(float angle){
  transform.rotation = angle;
};
void gameObject::Scale(float x, float y){
  transform.scale = {x, y};
};
void gameObject::Bind(unsigned int unit){
  sprite.bind(unit);
};
void gameObject::ShaderUse(){
  shader.use();
};
void gameObject::UpdateTex(const std::string& path, unsigned int unit){
  sprite.updateTex(path, unit);
};
void gameObject::SetProjection(int width, int height)
{
    glm::mat4 projection = glm::ortho(
        0.0f,
        (float)width,
        (float)height,
        0.0f
    );

    shader.use();
    shader.setMat4("projection", projection);
}
