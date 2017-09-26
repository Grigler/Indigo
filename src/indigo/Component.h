#ifndef __IND_COMPONENT__
#define __IND_COMPONENT__

class GameObj;

class Component
{

protected:

  GameObj* parentObj;

  virtual void OnUpdate() {};
  virtual void OnDestroy() {};
  virtual void OnFixedUpdate() {};

  GameObj* GetGameObj() 
  {
    return parentObj;
  }

  Component(GameObj* _parent)
  {
    parentObj = _parent;
  }

};


#endif