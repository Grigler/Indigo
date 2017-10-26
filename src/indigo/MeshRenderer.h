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

    void onUpdate();

    void LoadMesh(std::string _path);

    //Called by GO
    void Draw();
  private:
    std::shared_ptr<Mesh> mesh;
    //Uses MeshShader from meshShader.h by default
    std::shared_ptr<Shader> shader;
  };
}
#endif