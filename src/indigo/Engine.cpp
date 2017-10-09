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
  for (size_t i = 0; i < allMemObjs.size(); i++)
  {
    allMemObjs.at(i).reset();
  }
  allMemObjs.clear();

  for (size_t i = 0; i < gameObjects.size(); i++)
  {
    gameObjects.at(i).reset();
  }
  gameObjects.clear();
}

void Engine::Update()
{
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    GameObject *obj = (*i).get();
    if (obj == nullptr)
    {
      //stuff
      Application::ErrPrint(std::exception("gameObjects list holds nullptr"));
    }
    else
    {
      obj->Update();
    }
  }

  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    GameObject *obj = (*i).get();
    if (obj == nullptr)
    {
      //This shouldn't happen
      Application::ErrPrint(std::exception("gameObjects list holds nullptr"));
    }
    else
    {
      obj->LateUpdate();
    }
  }

  for (auto i = messageQueue.begin(); i != messageQueue.end(); i++)
  {
    Message m = (*i);
    m.to.lock()->RecieveMessage(m.msg, m.from);
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

void Engine::RegisterGameObject(GameObject *_obj)
{
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    if ((*i).get() == _obj)
    {
      Application::ErrPrint("Repeated GameObject Registration");
      return;
    }
  }
  gameObjects.push_back(std::shared_ptr<GameObject>(_obj));
}

void Engine::RegisterMsg(Message _msg)
{
  messageQueue.push_back(_msg);
}