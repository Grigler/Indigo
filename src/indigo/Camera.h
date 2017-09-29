#ifndef __IND_CAMERA__
#define __IND_CAMERA__

#include <glm/glm.hpp>

#include <list>

#include "Component.h"

namespace Indigo
{

  class Texture;
  class Window;
  class GameObj;

  class Camera : public Component
  {
    friend class Render;

  public:
    Camera(GameObj *_parent);
    ~Camera();

    bool isActive;

    void SetRenderToTexture(Texture *_text);
    void SetRenderToWindow(Window *_window);

  private:
    glm::mat4 proj;
    Texture *renderTexture;

    //Assumes that the list passed in is optimal for drawing
    //as is required
    void Render(std::list<GameObj*> _toDraw);
  };

} //End of namespace

#endif