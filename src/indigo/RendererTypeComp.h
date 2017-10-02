#ifndef __IND_RENDERER_TYPE_COMPONENT__
#define __IND_RENDERER_TYPE_COMPONENT__

#include "Component.h"

namespace Indigo
{
  class Transform;
  class Camera;

  //Base class that each GameObj contains a single instance of for drawing
  class RendererTypeComp : public Component
  {
  public:
    virtual void Draw(Camera *_c, Transform *_trans) {}
  };

} //End of namespace

#endif