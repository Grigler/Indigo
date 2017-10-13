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
  glm::vec3 transVec = pos * rot * scale * glm::vec3(1);
  glm::mat4 modelMat = glm::translate(glm::mat4(), transVec);
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

glm::mat4 Transform::_RotVecToMat()
{
  return glm::mat4(
    glm::rotate(glm::radians(rot.x), glm::vec3(1, 0, 0)) *
    glm::rotate(glm::radians(rot.y), glm::vec3(0, 1, 0)) *
    glm::rotate(glm::radians(rot.z), glm::vec3(0, 0, 1))
  );
}