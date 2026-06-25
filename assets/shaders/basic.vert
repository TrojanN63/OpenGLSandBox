#version 330 core

layout (location = 0) in vec3 aPos;

uniform float angle;

void main()
{
  float c = cos(angle);
  float s = sin(angle);

  mat4 roty = mat4(
    c, 0.0, s, 0.0,
    0.0, 1.0, 0.0, 0.0,
    -s, 0.0, c, 0.0,
    0.0, 0.0, 0.0, 1.0
  );

  gl_Position = roty * vec4(aPos, 1.0);
}
