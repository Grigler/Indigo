#include "Transform.h"

#include "GameObject.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace Indigo;

#define SET_AABB_RECALC_FLAG _aabbNeedRecalc = true;

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
  return glm::normalize((glm::vec3)(GetRotationMat() * forward));
}
glm::vec3 Transform::GetUp()
{
  glm::vec4 up(0, 1, 0, 1);
  return glm::normalize((glm::vec3)(GetRotationMat() * up));
}
glm::vec3 Transform::GetLeft()
{
  return glm::cross(GetUp(), GetForward());
}
glm::vec3 Transform::GetRight()
{
	return -GetLeft();
}

glm::mat3 Transform::GetRotationMat()
{
  glm::mat4 from = glm::mat4(1);
  if (!parent.expired())
  {
    from = parent.lock()->transform->GetRotationMat();
  }
  glm::mat4 rotationMat = glm::rotate(from, rot.y, glm::vec3(0, 1, 0));
  rotationMat = glm::rotate(rotationMat, rot.z, glm::vec3(0, 0, 1));
  rotationMat = glm::rotate(rotationMat, rot.x, glm::vec3(1, 0, 0));
  return rotationMat;
}
glm::quat Transform::GetRotationQuat()
{
  return glm::quat(GetRotationMat());
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
  glm::mat4 translationMat = glm::translate(from, glm::vec3(pos.x, pos.y, pos.z));
  glm::mat4 rotationMat = glm::rotate(from, rot.y, glm::vec3(0, 1, 0));
  rotationMat = glm::rotate(rotationMat, rot.z, glm::vec3(0, 0, 1));
  rotationMat = glm::rotate(rotationMat, rot.x, glm::vec3(1, 0, 0));
  
  glm::mat4 scaleMat = glm::scale(scale);

  glm::mat4 modelMat = translationMat*rotationMat*scaleMat;
  return modelMat;
}
glm::mat4 Transform::GetModelMatWithOffset(glm::vec3 _offset)
{
  //Starting from either an identity matrix if it has no parent
  //or from the model matrix of its parent
  glm::mat4 from = glm::mat4(1);
  if (!parent.expired())
  {
    from = parent.lock()->transform->GetModelMat();
  }
  //Converting translation, rotation and scale to matricies
  glm::mat4 translationMat = glm::translate(from, glm::vec3(pos.x, pos.y, pos.z)+_offset);
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
  SET_AABB_RECALC_FLAG
}
void Transform::MoveTo(glm::vec3 _target, float _alpha)
{
  glm::vec3 dir = glm::normalize(_target - pos);
  pos += dir*_alpha;
  SET_AABB_RECALC_FLAG
}
//Moves in _dir (world-space)
void Transform::MoveDir(glm::vec3 _dir, float _alpha)
{
  pos += _dir*_alpha;
  SET_AABB_RECALC_FLAG
}

void Transform::Rotate(glm::vec3 _eulerAngles)
{
  //rot += _eulerAngles;

  printf("Degr: %f, %f, %f\n", _eulerAngles.x, _eulerAngles.y, _eulerAngles.z);

  glm::vec3 rad = glm::radians(_eulerAngles);
  glm::quat q = rad;
  rot = rot * q;
  
  printf("NewROT: %f, %f, %f\n\n", rot.x, rot.y, rot.z);

  SET_AABB_RECALC_FLAG
}
void Transform::Scale(glm::vec3 _scaleBy)
{
  scale.x *= _scaleBy.x;
  scale.y *= _scaleBy.y;
  scale.z *= _scaleBy.z;
  SET_AABB_RECALC_FLAG
}

void Transform::onUpdate()
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