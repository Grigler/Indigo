#ifndef __IND_GAME_OBJ__
#define __IND_GAME_OBJ__

#include <memory>

class LinkedList;

class GameObj
{
  friend class Environment;
  friend class Scene;

public:
  std::unique_ptr<LinkedList> children;

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

#endif