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
    //GameObject();
    //GameObject(Transform _trans, std::shared_ptr<GameObject> *_parent = nullptr);
    //GameObject(glm::vec3 _pos, glm::vec3 _rot, std::shared_ptr<GameObject> *_parent = nullptr);

    static std::weak_ptr<GameObject> CreateObject(std::weak_ptr<GameObject> _parent);
    template <class T>
    static std::weak_ptr<T> CreateGameObject();

    virtual void Update() {}
    virtual void LateUpdate() {}
    virtual void Draw() {}

    //All derived GameObjects must contain a transform
    std::shared_ptr<Transform> transform;

	//template <class C>
	//void AddComponent();

  private:
    //GameObject();

    std::weak_ptr<GameObject> parent;
    std::vector<std::shared_ptr<Component>> components;

    static std::shared_ptr<GameObject> _MakeReg();
  };
  /*
  template <class C>
  void GameObject<C>::AddComponent()
  {
    std::shared_ptr<C> comp = std::make_shared(C);
    components.push_back(comp);
  }
  */
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