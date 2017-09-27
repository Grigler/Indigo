#include "Scene.h"

#include "GameObj.h"

using namespace Indigo;

Scene::Scene()
{

}

void Scene::tick()
{
  //Calling tick on all GameObjs in scene list
  for (std::list<GameObj*>::const_iterator i = topLevel.begin();
    i != topLevel.end(); i++)
  {
    (*i)->tick();
  }
}
//This is slow as fuck and super-unsafe
std::list<GameObj*> Scene::GetFullList()
{
  std::list<GameObj*> retList;
  retList = topLevel;

  for (std::list<GameObj*>::const_iterator i = retList.begin();
    i != retList.end(); i++)
  {
    for (std::list<GameObj*>::const_iterator j = (*i)->children.begin();
      j != (*i)->children.end(); j++)
    {
      retList.push_back((*j));
    }
  }

  return retList;
}