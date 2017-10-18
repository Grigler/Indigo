#ifndef __IND_MESH_RENDERER__
#define __IND_MESH_RENDERER__

#include <string>
#include <memory>

#include "RenderComponent.h"

namespace Indigo
{
  class Mesh;
  class Shader;

  class MeshRenderer : public RenderComponent
  {
    friend class Camera;
  public:
    MeshRenderer();

    void Update();

    void LoadMesh(std::string _path);

    //Called by GO
    void Draw();
  private:
    std::unique_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;
  };
}
#endif