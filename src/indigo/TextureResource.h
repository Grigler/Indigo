#ifndef __IND_TEXUTRE_RESOURCE__
#define __IND_TEXTURE_RESOURCE__

#include <string>

#include <GL/glew.h>

#include "resource.h"

namespace Indigo
{
  class TextureResource : public Resource
  {
    friend class Resources;
    friend class Texture;
  public:
    
    void Bind();

  private:
    std::string path;
    void ReadFromFile(std::string _path);

    void _loadPNG(std::string _path);

    GLuint id;
  };
}

#endif