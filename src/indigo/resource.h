#ifndef __IND_RESOURCE__
#define __IND_RESOURCE__

#include <string>

namespace Indigo
{
  class Resource
  {
    friend class Resources;
  private:
    std::string path;
    virtual void Load(std::string _path) {}
  };
}

#endif