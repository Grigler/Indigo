#include "Component.h"

#include "GameObj.h"

using namespace Indigo;

Component::Component(GameObj* _parent) 
{
  parentObj = _parent;
  _parent->RegisterComponent(this);
}
Component::~Component()
{
  parentObj->UnregisterComponent(this);
}

GameObj* Component::GetGameObj() 
{
  return parentObj;
}