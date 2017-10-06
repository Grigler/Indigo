#include "Engine.h"

#include "Application.h"
#include "GameObject.h"

using namespace Indigo;

void Engine::Update()
{
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    GameObject *obj = (*i).get();
    if (obj == 0)
    {
      //stuff
    }
    else
    {
      obj->Update();
    }
  }

  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    GameObject *obj = (*i).get();
    if (obj == 0)
    {
      //stuff
    }
    else
    {
      obj->LateUpdate();
    }
  }
}
void Engine::Draw()
{

}

void Engine::Register(std::shared_ptr<MemObj>& _obj)
{
  for (auto i = allMemObjs.begin(); i != allMemObjs.end(); i++)
  {
    if ((*i).get() == _obj.get())
    {
      Application::ErrPrint("Repeated MemObj Registration");
      return;
    }
  }
  allMemObjs.push_back(_obj);
}
void Engine::SweepDestroy()
{
  for (auto i = allMemObjs.begin(); i != allMemObjs.end(); i++)
  {
    MemObj *obj = (*i).get();
    if (obj == nullptr)
    {
      allMemObjs.erase(i);
    }
    else if (obj->readyToDestroy)
    {
      allMemObjs.erase(i);
    }
  }
}