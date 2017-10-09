#ifndef __IND_COMPONENT__
#define __IND_COMPONENT__

#include <memory>

namespace Indigo
{
  class GameObject;

  class Component
  {
    friend class Camera;
  public:
    Component(std::shared_ptr<GameObject> _parent);

    virtual void Update() {}
  protected:
    std::weak_ptr<GameObject> parent;
  };
}

#endif