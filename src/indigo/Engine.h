#ifndef __IND_ENGINE__
#define __IND_ENGINE__

#include <memory>
#include <vector>

#include "message.h"

namespace Indigo
{
  class Engine
  {
    friend class Application;
    friend class MemObj;
    friend class GameObject;
    friend class Camera;
  public:
    Engine();
    ~Engine();

  private:
    void Update();
    void Draw();

    std::shared_ptr<Camera> activeCamera;

    //MemObjs Memory register
    //TODO - ask Karsten about handling smart pointers in a vector
    std::vector<std::shared_ptr<MemObj>> allMemObjs;
    void RegisterMemObj(MemObj *_obj);
    void SweepDestroy();
    std::weak_ptr<MemObj> GetMemObjRef(MemObj *_obj);

    //Full list of gameObjects
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    //void RegisterGameObject(GameObject *_obj);
    void RegisterGameObject(std::shared_ptr<GameObject> _obj);

    //Message queue
    std::vector<Message> messageQueue;
    //MemObjs register messages that are then sent at the end of update
    void RegisterMsg(Message _msg);
  };
}
#endif