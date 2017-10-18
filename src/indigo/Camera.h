#ifndef __IND_CAMERA__
#define __IND_CAMERA__

#include "Component.h"

#include <glm/glm.hpp>

namespace Indigo
{
  class GameObject;

  class Camera : protected Component
  {
    friend class Engine;
    //Used to easily get current active camera
    friend class MeshRenderer;
  public:
    void Render();
    glm::mat4 GetIdentity();
  private:
    static bool LeftCloser(std::shared_ptr<GameObject> l, std::shared_ptr<GameObject> r);
    static std::weak_ptr<Camera> currentActive;
  };
}

#endif