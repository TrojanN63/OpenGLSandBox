#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 offset;
uniform float scale;
uniform float angle;

void main(){
  vec3 tPos = aPos;

  float c = cos(angle);
  float s = sin(angle);

  tPos = vec3(
    tPos.x * c - tPos.y * s,
    tPos.x * s + tPos.y * c,
    tPos.z
  );

  tPos *= scale;
  tPos.x += offset.x;
  tPos.y += offset.y;

  gl_Position = vec4(
    tPos,
    1.0
  );

  TexCoord = aTexCoord;
}
