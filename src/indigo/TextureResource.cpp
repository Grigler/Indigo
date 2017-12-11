#include "TextureResource.h"

#include "Application.h"

#include "lodepng.h"

using namespace Indigo;

void TextureResource::ReadFromFile(std::string _path)
{
  std::string extension;
  size_t i = _path.rfind('.', _path.length());
  if (i != std::string::npos)
  {
    extension = _path.substr(i + 1, _path.length() - i);
  }

  if (extension == "png")
  {
    path = _path;
    _loadPNG(_path);
  }
  else
  {
    Application::ErrPrint("Extension: " + extension + " not supported");
  }
}

void TextureResource::Bind()
{
  glBindTexture(GL_TEXTURE_2D, id);
}

void TextureResource::_loadPNG(std::string _path)
{
  unsigned int w = 0, h = 0;
  std::vector<unsigned char> data;
  std::vector<unsigned char> rawData;
  
  if (lodepng::load_file(data, _path))
  {
    Application::ErrPrint("Texture " + _path + " failed to load - using NULL texture");
    //Hard coded Magenta colour for NULL-texture vec4(1,0,1,1)
    rawData.push_back(255);
    rawData.push_back(0);
    rawData.push_back(255);
    rawData.push_back(255);
    w = 1; h = 1;
  }
  else
  {
    lodepng::decode(rawData, w, h, lodepng::State(), data);
  }
    
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &rawData[0]);
  glGenerateMipmap(GL_TEXTURE_2D);
}