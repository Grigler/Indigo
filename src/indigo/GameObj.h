#ifndef __IND_GAME_OBJ__
#define __IND_GAME_OBJ__

#include <memory>
#include <list>

namespace Indigo
{

  class Component;
  class Transform;

  class GameObj
  {
    friend class Environment;
    friend class Scene;
    friend class Component;

  public:
    GameObj();

    //Should change to safe pntr
    std::list<GameObj*> children;

    //Stub update functions
    virtual void onUpdate() {}
    virtual void onFixedUpdate() {}

    //Stub draw function
    //virtual void onDraw() {} -> Probably shouldn't be exposed to the engine users
    virtual void onPostDraw() {}

    Transform *trans;

  private:
    // All private functions can still be accessed by declared friend classes
    // but not game-devs thinking this is the update function if it was public
    void tick();

    std::list<Component*> components;
    void RegisterComponent(Component *_c);
    void UnregisterComponent(Component *_c);
  };

} //End of namespace

#endif