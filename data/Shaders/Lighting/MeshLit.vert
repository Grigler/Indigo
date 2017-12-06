#version 400

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 texCoords;

//Model-View-Projection
uniform mat4 modelMat;
uniform mat4 MVP;


out vec4 vertPos;
out vec3 vertNorm;
out vec2 uv;

void main()
{
  vertPos = modelMat * vec4(pos, 1.0f);
  vertNorm = norm;
  
  uv = texCoords;
  
  
  gl_Position = MVP * vec4(pos, 1.0f);
}