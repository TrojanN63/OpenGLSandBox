#pragma once
#include<string>
#include<glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    void setVec2(
      const std::string& name,
      float x,
      float y
    );

    void setFloat(
      const std::string& name,
      float f
    );

    void setMat4(
      const std::string& name,
      const glm::mat4& matrix
    );
};
