#include "GameObj.h"

#include "Component.h"
#include "Transform.h"

using namespace Indigo;

GameObj::GameObj()
{
  trans = new Transform(this);
}

void GameObj::tick()
{
  
}

void GameObj::RegisterComponent(Component *_c)
{
  for (std::list<Component*>::iterator i = components.begin();
    i != components.end(); i++)
  {
    if (_c == (*i))
    {
      return;
    }
  }
  components.push_back(_c);
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