#ifndef __IND_COMPONENT__
#define __IND_COMPONENT__

class Component
{

protected:
  virtual void OnUpdate() {};
  virtual void OnDestroy() {};
  virtual void OnFixedUpdate() {};

};


#endif