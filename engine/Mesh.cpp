#include "Mesh.hpp"

Mesh::Mesh(
  const std::vector<float>& vertices,
  const std::vector<unsigned int>& indices
){
  int indexCount = indices.size();

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
void Mesh::draw(int indexCount)
{
  glBindVertexArray(VAO);

  glDrawElements(
    GL_TRIANGLES,
    indexCount,
    GL_UNSIGNED_INT,
    0
  );
}
