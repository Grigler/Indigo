#ifndef __IND_RENDER_COMPONENT__
#define __IND_RENDER_COMPONENT__

#include "Component.h"

namespace Indigo
{
  class RenderComponent : public Component
  {
  public:

    virtual void Draw() {}

  private:
    //OGL interfacing stuff
  };
}

#endif