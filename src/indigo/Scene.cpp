#include "Scene.h"

#include "GameObj.h"

using namespace Indigo;

Scene::Scene()
{

}

void Scene::tick(float _dtS)
{
  //Calling tick on all GameObjs in scene list
  for (std::list<GameObj*>::const_iterator i = topLevel.begin();
    i != topLevel.end(); i++)
  {
    (*i)->tick(_dtS);
  }
}