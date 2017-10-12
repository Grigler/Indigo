#ifndef __IND_MESH__
#define __IND_MESH__

#include <string>

#include "resource.h"

namespace Indigo
{
  //TODO - pull apart obj loader for this
  class Mesh : public Resource
  {
    friend class Resources;
  public:

  private:
    std::string path;
    void ReadFromFile(std::string _path) { printf("This is just a test"); }
  };

}

#endif