#include "GameObj.h"

using namespace Indigo;

void GameObj::tick()
{
  
}

void GameObj::UnregisterComponent(Component *_c)
{
  for (std::list<Component*>::iterator i = components.begin();
    i != components.end(); i++)
  {
    if (_c == (*i))
    {
      components.erase(i);
      return;
    }
  }
}