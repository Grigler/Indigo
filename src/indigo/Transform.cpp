#include "Transform.h"
#include "Environment.h"

#include "glm/gtx/transform.hpp"
#include "glm/gtx/vector_angle.hpp"

using namespace Indigo;

glm::vec4 Transform::GetPosition()
{
  return position;
}
glm::vec4 Transform::GetRelative(glm::vec3 _in)
{
  glm::vec4 in4 = glm::vec4(_in, 1);
  glm::mat4 mat = glm::translate(glm::vec3(position.x, position.y, position.z));

  mat = mat *
    glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
    glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
    glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));

  return mat*in4;

}
glm::vec3 Transform::GetRotation()
{
  return rotation;
}
glm::vec3 Transform::GetScale()
{
  return scale;
}
glm::vec3 Transform::GetForward()
{
  glm::vec4 forward(0, 0, 1, 1);
  glm::mat4 rot = 
    glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
    glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
    glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));

  return glm::normalize((glm::vec3)(rot*forward));
}
glm::vec3 Transform::GetUp()
{
  glm::vec4 up(0, 1, 0, 1);
  glm::mat4 rot =
    glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
    glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
    glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));

  return glm::normalize((glm::vec3)(rot*up));
}
glm::vec3 Transform::GetRight()
{
  return glm::cross(GetUp(), GetForward());
}

void Transform::SetPosition(glm::vec4 _position)
{
  position = _position;
}

void Transform::SetRotation(glm::vec3 _rotation)
{
  rotation = _rotation;
}

void Transform::SetScale(glm::vec3 _scale)
{
  scale = _scale;
}

void Transform::Translate(glm::vec4 _translation)
{
  position += _translation;
}
void Transform::SmoothMove(glm::vec3 _dir, float _speed)
{
  position += (glm::vec4(_dir,1)*(_speed*Environment::GetDT()));
}
void Transform::MoveTowards(glm::vec3 _target, float _speed)
{
  glm::vec3 dir = glm::normalize(_target - glm::vec3(position.x, position.y, position.z));
  position += glm::vec4((dir*(_speed)), 1.0f);
}
void Transform::MoveForward(float _speed)
{
  position = GetRelative(glm::vec3(0, 0, 1.0f * _speed));
}
void Transform::MoveBackwards(float _speed)
{
  position = GetRelative(glm::vec3(0, 0, -1.0f * _speed));
}
void Transform::MoveRight(float _speed)
{
  position = GetRelative(glm::vec3(1.0f * _speed, 0, 0));
}
void Transform::MoveLeft(float _speed)
{
  position = GetRelative(glm::vec3(-1.0f * _speed, 0, 0));
}

void Transform::Rotate(glm::vec3 _rotation)
{
  rotation += _rotation;
}

void Transform::Scale(glm::vec3 _scaleBy)
{
  scale += _scaleBy;
}


Transform::Transform(GameObj* _parent):Component(_parent)
{
  scale = glm::vec3(1, 1, 1);
}