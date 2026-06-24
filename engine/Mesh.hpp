#pragma once

#include<vector>
#include<glad/gl.h>

class Mesh{
public:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  int indexCount;

  Mesh(
    const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices
  );

  void addAttribute(
    GLuint index,
    GLuint size,
    GLsizei stride,
    size_t offset
  );

  void finish();

  void draw();
};
