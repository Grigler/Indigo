#include "Transform.h"
#include "Environment.h"

using namespace Indigo;

glm::vec4 Transform::GetPosition()
{
  return position;
}

glm::quat Transform::GetRotation()
{
  return rotation;
}

glm::vec3 Transform::GetScale()
{
  return scale;
}

void Transform::SetPosition(glm::vec4 _position)
{
  position = _position;
}

void Transform::SetRotation(glm::quat _rotation)
{
  rotation = _rotation;
}

void Transform::SetScale(glm::vec3 _scale)
{
  scale = _scale;
}

void Transform::translate(glm::vec4 _translation)
{
  position += _translation;
}

void Transform::Rotate(glm::quat _rotation)
{
  rotation += _rotation;
}

void Transform::Scale(glm::vec3 _scaleBy)
{
  scale += _scaleBy;
}

void Transform::Move(glm::vec3 _direction, float _speed)
{
  position += (_direction*(_speed*Environment::GetDT()));
}

Transform::Transform(GameObj* _parent):Component(_parent)
{
  forward = glm::vec3(1, 0, 0);
  scale = glm::vec3(1, 1, 1);
}