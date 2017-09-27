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
    //Euler angles for simplicity
    glm::vec3 rotation;
    glm::vec3 scale;

  public:
    Transform(GameObj* _parent);

    glm::vec4 GetPosition();
    //Returns the position _in units away from this Objs position
    //Allowing simple movement with position = GetRelative(1,0,1);
    //for diagonal movement for example
    glm::vec4 GetRelative(glm::vec3 _in);
    glm::vec3 GetRotation();
    glm::vec3 GetScale();
    glm::vec3 GetForward();
    glm::vec3 GetUp();
    glm::vec3 GetRight();
    
    void SetPosition(glm::vec4 _position);
    void SetRotation(glm::vec3 _rotation);
    void SetScale(glm::vec3 _scale);

    void Translate(glm::vec4 _translation);
    //Lerps position over - takes account of delta time
    void SmoothMove(glm::vec3 _dir, float _speed);
    void MoveTowards(glm::vec3 _target, float _speed);
    void MoveForward(float _speed);
    void MoveBackwards(float _speed);
    void MoveRight(float _speed);
    void MoveLeft(float _speed);

    void Rotate(glm::vec3 _rotation);
    void Scale(glm::vec3 _scaleBy);

  };

}
#endif