#ifndef __IND_COMPONENT__
#define __IND_COMPONENT__

#include <memory>

#include "MemObj.h"

namespace Indigo
{
  class GameObject;
  class Transform;
  struct Collision;

  class Component : public MemObj
  {
    friend class Camera;
    friend class GameObject;
  public:
    virtual void onCreation() {}
    virtual void onUpdate() {}
    virtual void onFixedUpdate() {}
    virtual void onLateUpdate() {}

    //TODO
    //Called by GO when collision is detected
    //virtual void onCollision(std::weak_ptr<Collision> _other) {}

    //TODO - add more virtual functions
    void ParentTo(std::weak_ptr<GameObject> _go);

    std::weak_ptr<GameObject> parent;
    std::weak_ptr<Transform> transform;

  };
}

#endif