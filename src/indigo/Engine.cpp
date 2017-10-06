#include "Engine.h"

#include "Application.h"
#include "GameObject.h"
#include "message.h"

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

  for (auto i = messageQueue.begin(); i != messageQueue.end(); i++)
  {
    Message m = (*i);
    m.to.lock()->RecieveMessage(m.msg, m.from);
  }
  messageQueue.clear();
}
void Engine::Draw()
{

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