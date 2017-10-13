#ifndef __IND_TEXUTRE_RESOURCE__
#define __IND_TEXTURE_RESOURCE__

#include <string>

#include "resource.h"

namespace Indigo
{
  class TextureResource : public Resource
  {
    friend class Resources;
  public:
    
  private:
    std::string path;
    void ReadFromFile(std::string _path) {}
  };
}

#endif