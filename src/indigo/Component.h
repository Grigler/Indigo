#ifndef __IND_COMPONENT__
#define __IND_COMPONENT__

#include <memory>

namespace Indigo
{
  class GameObject;

  class Component
  {
    friend class Camera;
    friend class GameObject;
  public:
    virtual void onCreation() {}
    virtual void onUpdate() {}
    //TODO - add more virtual functions
    void ParentTo(std::weak_ptr<GameObject> _go);
  protected:
    std::weak_ptr<GameObject> parent;

  };
}

#endif