#include "Transform.h"

#include "GameObject.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace Indigo;

Transform::Transform( glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
{
  pos = _pos;
  rot = _rot;
  scale = _scale;
  _aabbNeedRecalc = false;
}

glm::vec3 Transform::GetForward()
{
  glm::vec4 forward(0, 0, 1, 1);
  return glm::normalize((glm::vec3)(_RotVecToMat() * forward));
}
glm::vec3 Transform::GetUp()
{
  glm::vec4 up(0, 1, 0, 1);
  return glm::normalize((glm::vec3)(_RotVecToMat() * up));
}
glm::vec3 Transform::GetRight()
{
  return glm::cross(GetUp(), GetForward());
}

glm::mat4 Transform::GetModelMat()
{
  //TODO - cache the model matrix as it is calculated

  //Starting from either an identity matrix if it has no parent
  //or from the model matrix of its parent
  glm::mat4 from = glm::mat4(1);
  if (!parent.expired())
  {
    from = parent.lock()->transform->GetModelMat();
  }
  //Converting translation, rotation and scale to matricies
  glm::mat4 translationMat = glm::translate(from, pos);
  glm::mat4 rotationMat = glm::rotate(from, rot.y, glm::vec3(0, 1, 0));
  rotationMat = glm::rotate(rotationMat, rot.z, glm::vec3(0, 0, 1));
  rotationMat = glm::rotate(rotationMat, rot.x, glm::vec3(1, 0, 0));
  
  glm::mat4 scaleMat = glm::scale(scale);

  glm::mat4 modelMat = translationMat*rotationMat*scaleMat;
  return modelMat;
}

void Transform::Translate(glm::vec3 _by)
{
  pos += _by;
}
void Transform::MoveTo(glm::vec3 _target, float _alpha)
{
  glm::vec3 dir = glm::normalize(_target - pos);
  pos += dir*_alpha;
}
void Transform::MoveDir(glm::vec3 _dir, float _alpha)
{
  pos += _dir*_alpha;
}

void Transform::Rotate(glm::vec3 _eulerAngles)
{
  rot += _eulerAngles;
  _aabbNeedRecalc = true;
}
void Transform::Scale(glm::vec3 _scaleBy)
{
  scale.x *= _scaleBy.x;
  scale.y *= _scaleBy.y;
  scale.z *= _scaleBy.z;
  _aabbNeedRecalc = true;
}

void Transform::Update()
{
  //Resetting flag for AABB
  _aabbNeedRecalc = false;
}
//Gets local rotation in matrix form
glm::mat4 Transform::_RotVecToMat()
{
  glm::mat4 rotationMat = glm::rotate(glm::mat4(1), rot.y, glm::vec3(0, 1, 0));
  rotationMat = glm::rotate(rotationMat, rot.z, glm::vec3(0, 0, 1));
  rotationMat = glm::rotate(rotationMat, rot.x, glm::vec3(1, 0, 0));
  return rotationMat;
}