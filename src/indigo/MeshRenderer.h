#ifndef __IND_MESH_RENDERER__
#define __IND_MESH_RENDERER__

#include <string>
#include <memory>

#include "Component.h"

namespace Indigo
{
  class Mesh;

  class MeshRenderer : public Component
  {
  public:
    void Update();
    void LoadMesh(std::string _path);
  private:
    std::weak_ptr<Mesh> mesh;
  };
}
#endif