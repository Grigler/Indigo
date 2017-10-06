#ifndef __IND_COMPONENT__
#define __IND_COMPONENT__

#include <memory>

namespace Indigo
{
  class GameObject;

  class Component
  {
  public:
    Component(std::shared_ptr<GameObject> _parent);

    virtual void Update() {}
  private:
    std::weak_ptr<GameObject> parent;
  };
}

#endif