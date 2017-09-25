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

  private:
    //Should change to safe pntr
    std::list<GameObj*> topLevel;

  };

} //End of namespace

#endif