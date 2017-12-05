#ifndef __IND_ENGINE__
#define __IND_ENGINE__

#include <memory>
#include <vector>

#include "message.h"

//#include "../example/config.h"

namespace Indigo
{
#ifdef IND_USE_AUDIO
  class AudioManager;
#endif

  class Engine
  {
    friend class Application;
    friend class MemObj;
    friend class GameObject;
    friend class Camera;
    friend class PhysicsHandler;
  public:
    Engine();
    ~Engine();

    static bool isRunning;

  private:
    void Update();
    void FixedUpdate();
    void Draw();

    std::shared_ptr<Camera> activeCamera;

    std::vector<std::shared_ptr<MemObj>> allMemObjs;
    void RegisterMemObj(MemObj *_obj);
    void SweepDestroy();
    std::weak_ptr<MemObj> GetMemObjRef(MemObj *_obj);

    //Full list of gameObjects
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::shared_ptr<GameObject>> goBuffer;
    std::weak_ptr<GameObject> Engine::GetGameObjRef(GameObject *_obj);
    //Pushes _obj to a buffer to be pushed to main vector next tick
    void RegisterGameObject(std::shared_ptr<GameObject> _obj);

    //Message queue
    std::vector<Message> messageQueue;
    //MemObjs register messages that are then sent at the end of update
    void RegisterMsg(Message _msg);

    //PhysicsHandler
    std::unique_ptr<PhysicsHandler> physicsHandler;

#ifdef IND_USE_AUDIO
    std::unique_ptr<AudioManager> audioManager;
#endif
  };
}
#endif