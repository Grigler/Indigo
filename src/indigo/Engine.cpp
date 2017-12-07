#include "../example/config.h"

#include "Engine.h"

#include "Application.h"
#include "Transform.h"
#include "GameObject.h"
#include "Camera.h"
#include "message.h"

#ifdef IND_USE_AUDIO
  #include "AudioManager.h"
#endif

#include "PhysicsHandler.h"


using namespace Indigo;

bool Engine::isRunning = false;

Engine::Engine()
{
#ifdef IND_USE_AUDIO
  audioManager = std::make_unique<AudioManager>();
  if (!audioManager->Init())
  {
    Application::ErrPrint(std::exception());
  }
  else
  {
    printf("OpenAL Audio System Init\n");
  }
#else
  printf("No Audio System Init\n");
#endif

  physicsHandler = std::make_unique<PhysicsHandler>();
}

Engine::~Engine()
{
#ifdef IND_USE_AUDIO
  audioManager->Destroy();
  audioManager.reset();
#endif
  physicsHandler.reset();
}

void Engine::Update()
{
  //physicsHandler->BroadPhase();
  //physicsHandler->NarrowPhase();
  //physicsHandler->Integrate();

  //Calling Update for GOs
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    std::weak_ptr<GameObject> g = (*i);
    g.lock()->onUpdate();
    if (!g.expired())
    {
      for (auto j = g.lock()->components.begin(); j < g.lock()->components.end(); j++)
      {
        (*j)->onUpdate();
      }
    }
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
    for (auto j = (*i)->components.begin(); j < (*i)->components.end(); j++)
    {
      (*j)->onLateUpdate();
    }
  }

  //Appending goBuffer to gameObject list
  if (goBuffer.size() > 0)
  {
    for (auto i = goBuffer.begin(); i != goBuffer.end(); i++)
    {
      gameObjects.push_back((*i));
    }
    goBuffer.clear();
  }
}
void Engine::FixedUpdate()
{
  physicsHandler->BroadPhase();
  physicsHandler->NarrowPhase();
  physicsHandler->Integrate();

  //Calling Update for GOs
  for (auto i = gameObjects.begin(); i != gameObjects.end(); i++)
  {
    std::weak_ptr<GameObject> g = (*i);
    g.lock()->onFixedUpdate();
    if (!g.expired())
    {
      for (auto j = g.lock()->components.begin(); j < g.lock()->components.end(); j++)
      {
        (*j)->onFixedUpdate();
      }
    }
  }
}
void Engine::Draw()
{
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
  for (auto i = goBuffer.begin(); i != goBuffer.end(); i++)
  {
    if ((*i).get() == _obj)
      return std::weak_ptr<GameObject>((*i));
  }
  return std::weak_ptr<GameObject>();
}

void Engine::RegisterGameObject(std::shared_ptr<GameObject> _obj)
{
  if(isRunning)
    goBuffer.push_back(_obj);
  else
    gameObjects.push_back(_obj);
}

void Engine::RegisterMsg(Message _msg)
{
  messageQueue.push_back(_msg);
}