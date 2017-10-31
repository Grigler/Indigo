#ifndef __IND_CHARACTER_CONTROLLER__
#define __IND_CHARACTER_CONTROLLER__

#include "Component.h"

#include "Camera.h"

#include <glm/vec2.hpp>

namespace Indigo
{
  class CharacterController : public Component
  {
  public:

    float moveSpeed;
    
    glm::vec2 mouseSens;

    void onCreation();
    void onUpdate();

    Camera cam;

  private:
    glm::vec2 lastMouseDelta;

    void UpdateRotFromMouse();
    void UpdatePosFromKeys();
  };
}

#endif