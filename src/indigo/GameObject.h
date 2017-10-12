#ifndef __IND_GAME_OBJECT__
#define __IND_GAME_OBJECT__

#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "MemObj.h"

namespace Indigo
{
  class Component;
  class Transform;

  class GameObject : public MemObj
  {
  public:
    template <class T>
    static std::weak_ptr<T> CreateGameObject();

    virtual void Update() {}
    virtual void LateUpdate() {}
    virtual void Draw() {}

    //All derived GameObjects must contain a transform
    std::shared_ptr<Transform> transform;

    void ParentTo(std::weak_ptr<GameObject> _go);
    //Returns weak_ptr reference to parent
    //No gurrantee that this isn't a nullptr
    std::weak_ptr<GameObject> GetParent();

    //Creates, adds and returns new instance of C component
	  template <class C>
	  std::weak_ptr<C> AddComponent(C _c);

  private:
    //GameObject();

    std::weak_ptr<GameObject> parent;
    std::vector<std::shared_ptr<Component>> components;

    static std::shared_ptr<GameObject> _MakeReg();
  };
  
  template <class C>
  std::weak_ptr<C> GameObject::AddComponent(C _c)
  {
    static_assert(std::is_convertible<C, GameObject>, "Must be a derived class of GameObject");
    static_assert(!std::is_class<C, Transform>, "Cannot add multiple transforms to same object");
    
    std::shared_ptr<C> rtn = std::make_shared<C>();
    components.push_back(rtn);
    
    return std::weak_ptr(rtn);
  }
  
  template <class T>
  std::weak_ptr<T> GameObject::CreateGameObject()
  {
    static_assert(std::is_convertible<T, GameObject>(), "Must be a derived class of GameObject");
    
    std::shared_ptr<T> rtn = std::make_shared<T>();
    Application::engineContext->RegisterGameObject(rtn);
    
    return std::weak_ptr<T>(rtn);
  }
}

#endif