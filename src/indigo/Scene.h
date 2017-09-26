#ifndef __IND_SCENE__
#define __IND_SCENE__

#include <memory>
#include <list>

namespace Indigo
{

  class GameObj;

  class Scene
  {
  public:
    Scene();

    void tick(float _dtS);
    //Expensive but traverses full scene and returns
    //full list of GameObjs in scene
    std::list<GameObj*> GetFullList();

  private:
    //Should change to safe pntr
    std::list<GameObj*> topLevel;

  };

} //End of namespace

#endif