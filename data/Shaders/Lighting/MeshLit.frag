#version 400

in vec4 vertPos;
in vec2 uv;

//Uniforms defining posiiton and direction of eye
uniform vec3 eyeDir;
uniform vec3 eyePos;

uniform sampler2D mainTexture;

out vec3 outCol;

void main()
{
  vec4 texColour = texture(mainTexture, uv);
  
}