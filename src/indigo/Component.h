#ifndef __IND_COMPONENT__
#define __IND_COMPONENT__

#include <memory>

namespace Indigo
{
  class GameObject;
  class Transform;
  struct Collision;

  class Component
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

    std::shared_ptr<GameObject> parent;
    std::shared_ptr<Transform> transform;

  };
}

#endif