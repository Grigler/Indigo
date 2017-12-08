#ifndef __IND_CAMERA__
#define __IND_CAMERA__

#include "Component.h"

#include "AABB.h"

#include <glm/glm.hpp>

namespace Indigo
{
  class GameObject;
  class RenderBuffer;

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

    void CalcFrustumBVPartitions(int _bvNum);

    float fov;
    float near, far;

    std::vector<AABB> frustumBVs;
    //Returns true on first frustumBVs collision and false if in none
    bool InFrustum(std::weak_ptr<AABB> _bv);

    static std::shared_ptr<RenderBuffer> rb;
  };
}

#endif