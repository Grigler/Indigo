#ifndef __IND_ENGINE__
#define __IND_ENGINE__

#include <memory>
#include <vector>

namespace Indigo
{
  class MemObj;
  class GameObject;

  class Engine
  {
    friend class Application;
  public:

  private:
    void Update();
    void Draw();

    std::vector<std::shared_ptr<MemObj>> allMemObjs;
    void Register(std::shared_ptr<MemObj>& _obj);
    void SweepDestroy();

    std::vector<std::shared_ptr<GameObject>> gameObjects;
  };
}
#endif