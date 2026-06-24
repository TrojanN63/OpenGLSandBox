#include "Shader.hpp"
#include "FileUtils.hpp"
#include <iostream>

Shader::Shader(
    const std::string& vertexPath,
    const std::string& fragmentPath
){
    std::string vertexSource = readFile(vertexPath);

    std::string fragmentSource = readFile(fragmentPath);

    const char* vertexCode = vertexSource.c_str();

    const char* fragmentCode = fragmentSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexCode,
        nullptr
    );

    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentCode,
        nullptr
    );

    glCompileShader(fragmentShader);

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setVec3(
    const std::string& name,
    float x,
    float y,
    float z
)
{
    GLint location =
        glGetUniformLocation(
            ID,
            name.c_str()
        );

    glUniform3f(
        location,
        x,
        y,
        z
    );
}

void Shader::setVec2(
    const std::string& name,
    float x,
    float y
)
{
    GLint location =
        glGetUniformLocation(
            ID,
            name.c_str()
        );

    glUniform2f(
        location,
        x,
        y
    );
}

void Shader::setInt(
    const std::string& name,
    int value
){
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(
    const std::string& name,
    float f
){
  glUniform1f(glGetUniformLocation(ID, name.c_str()), f);
}
