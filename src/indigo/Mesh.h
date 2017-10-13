#ifndef __IND_MESH__
#define __IND_MESH__

#include <memory>

#include "Component.h"

namespace Indigo
{
  class MeshResource;

  class Mesh
  {
    friend class MeshRenderer;
  public:
    void Assign(std::weak_ptr<MeshResource> _m);
  private:
    std::shared_ptr<MeshResource> mesh;
  };
}

#endif