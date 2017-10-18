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
  class MeshResource;
  class TextureResource;

  class Resources
  {
  public:
    virtual ~Resources() {}
    static std::weak_ptr<MeshResource> LoadMesh(std::string _path);
    static std::weak_ptr<TextureResource> LoadTexture(std::string _path);

  private:
    static std::vector<std::shared_ptr<MeshResource>> meshVec;
    static std::vector<std::shared_ptr<TextureResource>> textureVec;
  };

}

#endif