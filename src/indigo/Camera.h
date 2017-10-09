#ifndef __IND_CAMERA__
#define __IND_CAMERA__

#include "Component.h"

namespace Indigo
{
  class GameObject;

  class Camera : protected Component
  {
    friend class Engine;
  public:
    void Render();
  private:
    static bool LeftCloser(std::shared_ptr<GameObject> l, std::shared_ptr<GameObject> r);
    static Camera *currentActive;
  };
}

#endif