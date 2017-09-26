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
    //we are thinking about this wrong, a quat does not define what the rotation is, it is itself a rotation which is applied to a transformation matrix
    //soo this needs to be changed perhaps or maybe thought of differently by myself
    glm::quat rotation;
    glm::vec3 scale;
    glm::vec3 forward;

  public:
    Transform(GameObj* _parent);

    glm::vec4 GetPosition();
    glm::quat GetRotation();
    glm::vec3 GetScale();
    
    void SetPosition(glm::vec4 _position);
    //also this
    void SetRotation(glm::quat _rotation);
    void SetScale(glm::vec3 _scale);

    void translate(glm::vec4 _translation);
    //also this
    void Rotate(glm::quat _rotation);
    void Scale(glm::vec3 _scaleBy);

    void Move(glm::vec3 _direction, float _speed)

  };

}
#endif