#include "Mesh.hpp"

Mesh::Mesh(
  const std::vector<float>& vertices,
  const std::vector<unsigned int>& indices
){
  indexCount = indices.size();

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(
    GL_ARRAY_BUFFER,
    vertices.size() * sizeof(float),
    vertices.data(),
    GL_STATIC_DRAW
  );

  glBindBuffer(
    GL_ELEMENT_ARRAY_BUFFER,
    EBO
  );

  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indices.size() * sizeof(unsigned int),
    indices.data(),
    GL_STATIC_DRAW
  );
}
void Mesh::draw()
{
  glBindVertexArray(VAO);

  glDrawElements(
    GL_TRIANGLES,
    indexCount,
    GL_UNSIGNED_INT,
    0
  );
}
void Mesh::addAttribute(
    GLuint index,
    GLuint size,
    GLsizei stride,
    size_t offset
){
  glBindVertexArray(VAO);

  glVertexAttribPointer(
    index,
    size,
    GL_FLOAT,
    GL_FALSE,
    stride,
    (void*)offset
  );

  glEnableVertexAttribArray(index);
}
void Mesh::finish(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
