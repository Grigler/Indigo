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
  class RenderComponent;

  struct Contact;

  class GameObject
  {
    friend class Engine;
    friend class Camera;
  public:
    template <class T>
    static std::weak_ptr<T> CreateGameObject();

    virtual void onCreation() {}
    virtual void onUpdate() {}
    virtual void onFixedUpdate() {}
    virtual void onLateUpdate() {}

    //Calls onCollision function of all components
    void onCollision(std::weak_ptr<Contact> _contact);

    //Called by Camera when it is optimal for its draw call
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

    std::weak_ptr<RenderComponent> GetRenderComponent() {  return renderComponent;  }

  private:
    std::weak_ptr<GameObject> parent;

    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<RenderComponent> renderComponent;
    
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
    //std::dynamic_pointer_cast<T>(rtn)->onCreation();
    rtn->onCreation();
    
    return std::weak_ptr<T>(rtn);
  }
  template <class T>
  std::weak_ptr<T> GameObject::GetComponent()
  {
    static_assert(std::is_base_of<Component, T>(),
      "T must be a derived class of Component");

    for (auto i = components.begin(); i != components.end(); i++)
    {
      T *checkT = dynamic_cast<T*>((*i).get());

      if (checkT != nullptr)
      {
        return std::weak_ptr<T>(std::dynamic_pointer_cast<T>((*i)));
        
        //return std::weak_ptr<T>((*i));
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
      T *checkT = dynamic_cast<T*>((*i));

      if (checkT != nullptr)
      {
        rtn.push_back(std::weak_ptr(std::dynamic_pointer_cast<T>((*i)));)
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
    rtn->transform = std::make_shared<Transform>();

    Application::engineContext->RegisterGameObject(std::dynamic_pointer_cast<GameObject>(rtn));
    //Calling onCreation for GO
    rtn->onCreation();

    return std::weak_ptr<T>(rtn);
  }

}

#endif