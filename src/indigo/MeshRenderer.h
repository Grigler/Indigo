#ifndef __IND_MESH_RENDERER__
#define __IND_MESH_RENDERER__

#include <string>
#include <memory>

#include "RenderComponent.h"

namespace Indigo
{
  class Mesh;
  class Shader;
  class Texture;

  class MeshRenderer : public RenderComponent
  {
    friend class Camera;
  public:
    MeshRenderer();

    void onUpdate();

    void LoadMesh(std::string _path);
    void LoadTexture(std::string _path);

    //Called by GO
    void Draw();

    //DEBUG AS PUBLIC
    std::shared_ptr<Mesh> mesh;

  private:
    //Uses MeshShader from meshShader.h by default
    std::weak_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;
  };
}
#endif