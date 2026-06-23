#pragma once

#include<vector>
#include<glad/gl.h>

class Mesh{
public:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  Mesh(
    const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices
  );

  void draw(int);
};
