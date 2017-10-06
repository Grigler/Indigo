#include "Transform.h"

using namespace Indigo;

Transform::Transform(std::shared_ptr<GameObject> _parent, Transform _trans) : Component(_parent)
{
  pos = _trans.GetPosition();
  rot = _trans.GetRotation();
}
Transform::Transform(std::shared_ptr<GameObject> _parent, glm::vec3 _pos, glm::vec3 _rot) : Component(_parent)
{
  pos = _pos;
  rot = _rot;
}