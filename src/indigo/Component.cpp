#include "Component.h"


#include "GameObj.h"

using namespace Indigo;

Component::Component(GameObj* _parent) 
{
  parentObj = _parent;
}

GameObj* Component::GetGameObj() 
{
  return parentObj;
}

Component::~Component()
{
  parentObj->UnregisterComponent(this);
}