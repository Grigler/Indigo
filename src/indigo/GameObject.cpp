#include "GameObject.h"

#include "Application.h"
#include "Engine.h"

#include "Component.h"
#include "Transform.h"

using namespace Indigo;

/*
GameObject::GameObject()
{
  //Application::engineContext->RegisterGameObject(this);
}
GameObject::GameObject(Transform _trans, std::shared_ptr<GameObject> *_parent)
{
  transform = std::make_shared<Transform>(std::shared_ptr<GameObject>(this), _trans);
  if (_parent != nullptr)
  {
    parent = (*_parent);
  }
}
GameObject::GameObject(glm::vec3 _pos, glm::vec3 _rot, std::shared_ptr<GameObject> *_parent)
{
  transform = std::make_shared<Transform>(std::shared_ptr<GameObject>(this), _pos, _rot);
  if (_parent != nullptr)
  {
    parent = (*_parent);
  }
}
*/
std::weak_ptr<GameObject> GameObject::CreateObject(std::weak_ptr<GameObject> _parent)
{
  std::weak_ptr<GameObject> rtn(_MakeReg());
  rtn.lock()->parent = _parent;
  return rtn;
}

std::shared_ptr<GameObject> GameObject::_MakeReg()
{
  std::shared_ptr<GameObject> rtn = std::make_shared<GameObject>();
  Application::engineContext->RegisterGameObject(rtn);
  return rtn;
}