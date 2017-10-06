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
    Transform(std::shared_ptr<GameObject> _parent, glm::vec3 _pos, glm::vec3 _rot);

  private:
    glm::vec3 pos;
    glm::vec3 rot;
  };
}

#endif