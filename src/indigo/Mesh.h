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
    friend class Camera;
    //Needs to access RB and other mesh data
    friend class RB;
  public:
    Mesh();

    void Assign(std::weak_ptr<MeshResource> _m);
    void ActivateVAO();

    GLsizei GetVertCount();

  private:
    std::weak_ptr<GameObject> goParent;

    std::shared_ptr<MeshResource> meshResource;

    std::shared_ptr<AABB> aabb;
    void _updateAABB(glm::mat4 _modelMat);
  };
}

#endif