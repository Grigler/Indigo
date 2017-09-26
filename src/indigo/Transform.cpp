#include "Transform.h"

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

Transform::Transform(GameObj* _parent):Component(_parent)
{
  scale = glm::vec3(1, 1, 1);
}