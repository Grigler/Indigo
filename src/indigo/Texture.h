#ifndef __IND_TEXUTRE__
#define __IND_TEXTURE__

#include <string>

#include "resource.h"

namespace Indigo
{
  class Texture : public Resource
  {
    friend class Resources;
  public:
    
  private:
    std::string path;
    void ReadFromFile(std::string _path) {}
  };
}

#endif