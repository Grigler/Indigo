#ifndef __IND_CAMERA__
#define __IND_CAMERA__

#include <glm/glm.hpp>

#include "Component.h"

namespace Indigo
{

  class Texture;
  class Window;
  class GameObj;

  class Camera : public Component
  {
  public:
    Camera(GameObj *_parent);
    ~Camera();

    bool isActive;

    void SetRenderToTexture(Texture *_text);
    void SetRenderToWindow(Window *_window);

  private:
    glm::mat4 proj;
    Texture *renderTexture;

  };

} //End of namespace

#endif