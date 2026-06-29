#pragma once

#include<glad/gl.h>
#include<string>

class Texture{
public:
  GLuint ID;

  Texture(
    const std::string& path
  );

  void bind(unsigned int);
  void updateTex(const std::string& path, unsigned int);
};
