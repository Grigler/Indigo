#ifndef __IND_GAME_OBJ__
#define __IND_GAME_OBJ__

#include <memory>
#include <list>

namespace Indigo
{

  class Component;

  class GameObj
  {
    friend class Environment;
    friend class Scene;

  public:
    //Should change to safe pntr
    std::list<GameObj*> children;

    //Stub update functions
    virtual void onUpdate() {}
    virtual void onFixedUpdate() {}

    //Stub draw function
    virtual void onDraw() {}
    virtual void onPostDraw() {}

  private:

    // All private functions can still be accessed by declared friend classes
    // but not game-devs thinking this is the update function if it was public
    void tick(float _dtS);
  };

} //End of namespace

#endif