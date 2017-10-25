#include "Engine.h"

#include "Application.h"
#include "Transform.h"
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
  //Calling Update for GOs
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    (*i)->onUpdate();
  }
  //Calling callback funcs for all Messages
  for (auto i = messageQueue.begin(); i != messageQueue.end(); i++)
  {
    (*i).to.lock()->RecieveMessage((*i).msg, (*i).from);
  }
  messageQueue.clear();

  //Calling LateUpdate after everything else
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    (*i)->onLateUpdate();
  }
}
void Engine::Draw()
{
  //Call Render() on active camera
  /*
  if (activeCamera.get() != nullptr)
  {
    activeCamera->Render();
  }
  */
  if (Camera::currentActive.lock().get() != nullptr)
  {
    Camera::currentActive.lock()->Render();
  }
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
    if ((*i)->readyToDestroy)
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
std::weak_ptr<GameObject> Engine::GetGameObjRef(GameObject *_obj)
{
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    if ((*i).get() == _obj)
      return std::weak_ptr<GameObject>((*i));
  }
  return std::weak_ptr<GameObject>();
}
void Engine::RegisterGameObject(std::shared_ptr<GameObject> _obj)
{
  gameObjects.push_back(_obj);
}

void Engine::RegisterMsg(Message _msg)
{
  messageQueue.push_back(_msg);
}