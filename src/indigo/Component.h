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

    template<class T>
    std::weak_ptr<T> GetUpCastedSelfRef();

  private:
    std::weak_ptr<Component> refToThisComponent;
  };

  template<class T>
  std::weak_ptr<T> Component::GetUpCastedSelfRef()
  {
    static_assert(std::is_convertible<T, Component>(),
      "Type T must be derived or base of Component to be UpCasted");

    std::weak_ptr<T> rtn = std::dynamic_pointer_cast<T>(refToThisComponent);
    return rtn;
  }


}

#endif