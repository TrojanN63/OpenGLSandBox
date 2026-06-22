#pragma once
#include<string>
#include<glad/gl.h>

class Shader{
  public:
    GLuint ID;
    Shader(
        const std::string& vertexPath,
        const std::string& fragmentPath
    );
    void use();

    void setVec3(
      const std::string& name,
      float x,
      float y,
      float z
    );

    void setInt(
      const std::string& name,
      int value
    );
};
