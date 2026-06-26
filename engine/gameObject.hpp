#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include <vector>

struct Transform {
  float x, y;
  float angle;
  float scale;
};

class gameObject{
  public:

  gameObject(
    const std::string& vert,
    const std::string& frag,
    const std::string& spritePath,
    float sizex,
    float sizey
  );
  
  std::vector<float> vertices;

  std::vector<unsigned int> indices;

  GLint offset;
  GLint scale;
  GLint angle;

  Shader shader;
  Mesh mesh;
  Texture sprite;

  void Position(
    float x,
    float y
  );
  void Draw();

  void Rotation(
    float angle
  );

  void Scale(
    float scale
  );

  void Bind(
    unsigned int unit
  );

  void ShaderUse();

};
