#include"Texture.hpp"
#include<stb/stb_image.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

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

  if (data) {
    float r_mult = RGB[0], g_mult = RGB[1], b_mult = RGB[2];
    for (int i = 0; i < width * height; i++) {
      unsigned char *px = data + i * channels;
      int r = (int)(px[0] * r_mult);
      int g = (int)(px[1] * g_mult);
      int b = (int)(px[2] * b_mult);
      px[0] = (r > 255) ? 255 : (r < 0 ? 0 : r);
      px[1] = (g > 255) ? 255 : (g < 0 ? 0 : g);
      px[2] = (b > 255) ? 255 : (b < 0 ? 0 : b);
    }
}

  if (!data) {
    std::cout << "Falha ao carregar textura\n";
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

vector<float> Texture::RGB = {1.0f,1.0f,1.0f};

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
