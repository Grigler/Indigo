#ifndef __IND_MESH__
#define __IND_MESH__

#include <GL/glew.h>
#include <memory>

#include "Component.h"

#include "AABB.h"

namespace Indigo
{
  class MeshResource;

  class Mesh
  {
    friend class MeshRenderer;
  public:
    void Assign(std::weak_ptr<MeshResource> _m);
    void ActivateVAO();

    GLsizei GetVertCount();

  private:
    std::shared_ptr<MeshResource> meshResource;

    AABB aabb;
    void _updateAABB(glm::mat4 _modelMat);
  };
}

#endif