#ifndef __IND_TRANSFORM__
#define __IND_TRANSFORM__
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Indigo
{

  class Transform : public Component
  {
  private:
    glm::vec4 position;
    glm::quat rotation;
    glm::vec3 scale;

  public:
    Transform(GameObj* _parent);

    glm::vec4 GetPosition();
    glm::quat GetRotation();
    glm::vec3 GetScale();
    
    void SetPosition(glm::vec4 _position);
    void SetRotation(glm::quat _rotation);
    void SetScale(glm::vec3 _scale);
  };

}
#endif