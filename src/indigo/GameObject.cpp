#include "GameObject.h"

#include "Application.h"
#include "Engine.h"

#include "Component.h"
#include "Transform.h"

using namespace Indigo;

std::shared_ptr<GameObject> GameObject::_MakeReg()
{
  std::shared_ptr<GameObject> rtn = std::make_shared<GameObject>();
  Application::engineContext->RegisterGameObject(rtn);
  return rtn;
}

void GameObject::ParentTo(std::weak_ptr<GameObject> _go)
{
  //Changing parent weak_ptr to have access to shared_ptr
  //that _go has access to
  parent = _go;
}
std::weak_ptr<GameObject> GameObject::GetParent()
{
  return parent;
}