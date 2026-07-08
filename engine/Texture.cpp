#include"Texture.hpp"
#include<stb/stb_image.h>
#include<iostream>
#include<string>

Texture::Texture(const std::string& path){
  
  glGenTextures(1, &ID);

  glBindTexture(GL_TEXTURE_2D, ID);

  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_WRAP_S,
    GL_REPEAT
  );

  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_WRAP_T,
    GL_REPEAT
  );
  
  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MIN_FILTER,
    GL_NEAREST_MIPMAP_NEAREST
  );

  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MAG_FILTER,
    GL_NEAREST
  );

  stbi_set_flip_vertically_on_load(true);

  int width;
  int height;
  int channels;

  unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

  if (!data) {
    std::cout << "Falha ao carregar textura\n";
  }

  GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}
void Texture::bind(unsigned int unit)
{
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(
    GL_TEXTURE_2D,
    ID
  );
}
void Texture::updateTex(const std::string& path, unsigned int unit){
  int width;
  int height;
  int channels;

  unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

  if (!data) {
    std::cout << "Falha ao carregar textura\n";
  }

  GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(
    GL_TEXTURE_2D,
    ID
  );

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}
