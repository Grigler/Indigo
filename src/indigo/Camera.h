#ifndef __IND_CAMERA__
#define __IND_CAMERA__

#include "Component.h"

#include "AABB.h"

#include <glm/glm.hpp>

namespace Indigo
{
  class GameObject;

  class Camera : public Component
  {
    friend class Engine;
    //Used to easily get current active camera
    friend class MeshRenderer;
  public:
    void onCreation();
    void onLateUpdate();
    void Render();

    void MakeActive();
    static std::weak_ptr<Camera> currentActive;

    glm::mat4 GetViewProj();
  private:
    static bool LeftCloser(std::shared_ptr<GameObject> l, std::shared_ptr<GameObject> r);
    
    void CalcFrustumBV();

    float fov;

    //AABB BV formed from camera's frustum
    AABB frustumBV;
  };
}

#endif