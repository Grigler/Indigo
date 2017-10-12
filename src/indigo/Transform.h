#ifndef __IND_TRANSFORM__
#define __IND_TRANSFORM__

#include "Component.h"

#include <memory>

#include "glm/glm.hpp"

namespace Indigo
{
  class GameObject;

  class Transform : public Component
  {
  public:
    Transform() { pos = glm::vec3(0); rot = glm::vec3(0); }
    Transform(glm::vec3 _pos, glm::vec3 _rot);

    glm::vec3 GetPosition() { return pos; }
    glm::vec3 GetRotation() { return rot; }
  private:
    glm::vec3 pos;
    glm::vec3 rot;
  };
}

#endif