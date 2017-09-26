#include "Component.h"
#include "GameObj.h"

Component::Component(GameObj* _parent) 
{
  parentObj = _parent;
}

GameObj* Component::GetGameObj() 
{
  return parentObj;
}