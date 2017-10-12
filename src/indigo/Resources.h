#ifndef __IND_RECOURCES__
#define __IND_RECOURCES__

#define STRINGIFY(T) #T

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "resource.h"

namespace Indigo
{
  class Mesh;
  class Texture;

  class Resources
  {
  public:
    static std::weak_ptr<Mesh> LoadMesh(std::string _path);
    static std::weak_ptr<Texture> LoadTexture(std::string _path);

  private:
    static std::vector<std::shared_ptr<Mesh>> meshVec;
    static std::vector<std::shared_ptr<Texture>> textureVec;
  };

}

#endif