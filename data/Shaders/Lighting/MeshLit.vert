#version 400

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;

layout (location = 2) in vec2 texCoords;

//Model-View-Projection
uniform mat4 MVP;

//Arbitrary value
#define MAX_POINT_LIGHTS 16;

uniform int numPointLights;
uniform struct PointLight
{
  vec4 pos;
  
  
}

out vec4 vertPos;
out vec2 uv;

void main()
{
  vertPos = MVP * vec4(pos, 1.0f);
  uv = texCoords;
  
  
  gl_Position = vertPos;
}