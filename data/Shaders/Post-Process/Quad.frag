layout (location = 0) out vec4 outCol;

uniform sampler2D texColour;
uniform sampler2D texDepth;

in vec2 texCoord;

void main()
{
  outCol = texture(texColour, uv);
}