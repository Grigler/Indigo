#ifndef __IND_MESH_RENDERER__
#define __IND_MESH_RENDERER__

#include <string>
#include <memory>

#include "RenderComponent.h"

namespace Indigo
{
  class Mesh;

  class MeshRenderer : public RenderComponent
  {
  public:
    MeshRenderer();

    void Update();
    void LoadMesh(std::string _path);
  private:
    std::unique_ptr<Mesh> mesh;
  };
}
#endif