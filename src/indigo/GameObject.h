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
	  template <class T>
	  std::weak_ptr<T> AddComponent();
    template <class T>
    //Returns first found instance of T in components list
    std::weak_ptr<T> GetComponent();
    template <class T>
    //Returns vector of all found instances of T in components list
    std::vector<std::weak_ptr<T>> GetComponents();

  private:
    std::weak_ptr<GameObject> parent;

    std::vector<std::shared_ptr<Component>> components;
    
    static std::shared_ptr<GameObject> _MakeReg();
  };
  
  template <class T>
  std::weak_ptr<T> GameObject::AddComponent()
  {
    static_assert(std::is_base_of<Component, T>(),
      "Added Component must be a derived class of Component, not the base Component");
    static_assert(!std::is_same<T, Transform>(),
      "Cannot add multiple transforms to same GameObject");
    
    std::shared_ptr<T> rtn = std::make_shared<T>();
    rtn->ParentTo(Application::engineContext->GetGameObjRef(this));

    components.push_back(rtn);
    
    return std::weak_ptr<T>(rtn);
  }
  template <class T>
  std::weak_ptr<T> GameObject::GetComponent()
  {
    static_assert(std::is_base_of<Component, T>(),
      "T must be a derived class of Component");

    for (auto i = components.begin(); i != components.end(); i++)
    {
      if (std::is_same<T, (*i)>())
      {
        return std::weak_ptr<T>((*i));
      }
    }

    return std::weak_ptr<T>();
  }
  template <class T>
  std::vector<std::weak_ptr<T>> GameObject::GetComponents()
  {
    static_assert(std::is_base_of<Component, T>(),
      "T must be a derived class of Component");

    std::vector<std::weak_ptr<T>> rtn;
    for (auto i = components.begin(); i != components.end(); i++)
    {
      if (std::is_same < T, (*i))
      {
        rtn.push_back(std::weak_ptr((*i));)
      }
    }

    return rtn;
  }

  template <class T>
  std::weak_ptr<T> GameObject::CreateGameObject()
  {
    static_assert(std::is_convertible<T, GameObject>(),
      "Created Object must be a derived class of GameObject or base GameObject");
    
    std::shared_ptr<T> rtn = std::make_shared<T>();
    Application::engineContext->RegisterGameObject(rtn);
    
    rtn->transform = std::make_shared<Transform>();

    return std::weak_ptr<T>(rtn);
  }
  
}

#endif