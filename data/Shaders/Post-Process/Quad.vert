
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 uv;

void main()
{
  uv = texCoord;
  gl_position = ve4(pos, 1);
}