#pragma once

#include<glad/gl.h>
#include<string>
#include<vector>

class Texture{
public:
  GLuint ID;
  static std::vector<float> RGB;

  Texture(
    const std::string& path
  );

  void bind(unsigned int);
  void updateTex(const std::string& path, unsigned int);
};
