#include "Engine.h"

#include "Application.h"
#include "GameObject.h"
#include "Camera.h"
#include "message.h"


using namespace Indigo;

Engine::Engine()
{

}
Engine::~Engine()
{

}

void Engine::Update()
{
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    (*i)->Update();
  }

  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    (*i)->LateUpdate();
  }

  for (auto i = messageQueue.begin(); i != messageQueue.end(); i++)
  {
    (*i).to.lock()->RecieveMessage((*i).msg, (*i).from);
  }
  messageQueue.clear();
}
void Engine::Draw()
{
  //Call Render() on active camera
  if(activeCamera.get() != nullptr)
    activeCamera->Render();
}

void Engine::RegisterMemObj(MemObj *_obj)
{
  for (auto i = allMemObjs.begin(); i != allMemObjs.end(); i++)
  {
    if ((*i).get() == _obj)
    {
      Application::ErrPrint("Repeated MemObj Registration");
      return;
    }
  }
  allMemObjs.push_back(std::shared_ptr<MemObj>(_obj));
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
std::weak_ptr<MemObj> Engine::GetMemObjRef(MemObj *_obj)
{
  for (auto i = allMemObjs.begin(); i != allMemObjs.end(); i++)
  {
    if ((*i).get() == _obj)
      return std::weak_ptr<MemObj>((*i));
  }
  return std::weak_ptr<MemObj>();
}
void Engine::RegisterGameObject(std::shared_ptr<GameObject> _obj)
{
  gameObjects.push_back(_obj);
}

void Engine::RegisterMsg(Message _msg)
{
  messageQueue.push_back(_msg);
}