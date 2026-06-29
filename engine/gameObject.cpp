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
  
  offset = glGetUniformLocation(shader.ID, "offset");
  scale = glGetUniformLocation(shader.ID, "scale");
  angle = glGetUniformLocation(shader.ID, "angle");
 
};
void gameObject::Position(
    float x,
    float y
){
  shader.setVec2("offset", x, y);
};
void gameObject::Draw(){
  shader.use();
  sprite.bind(0);
  mesh.draw();
};
void gameObject::Rotation(float angle){
  shader.setFloat("angle", angle);
};
void gameObject::Scale(float scale){
  shader.setFloat("scale", scale);
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
