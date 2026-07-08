#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Transform {
  glm::vec2 position = {0,0};
  glm::vec2 scale = {0,0};
  float rotation = 0.0f;
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

  Transform transform;

  Shader shader;
  Mesh mesh;
  Texture sprite;

  void Position(
    float x,
    float y
  );
  glm::mat4 GetModelMatrix() const;

  void Rotation(
    float angle
  );

  void Scale(
    float x,
    float y
  );

  void UpdateTex(
    const std::string& path,
    unsigned int unit
  );

};
