#include "GameObject.h"

#include "Component.h"
#include "Transform.h"

using namespace Indigo;

GameObject::GameObject()
{

}
GameObject::GameObject(Transform _trans, std::shared_ptr<GameObject> *_parent)
{
  transform = std::make_shared<Transform>(_trans);
  if (_parent != nullptr)
  {
    parent = (*_parent);
  }
}
GameObject::GameObject(glm::vec3 _pos, glm::vec3 _rot, std::shared_ptr<GameObject> *_parent)
{
  transform = std::make_shared<Transform>(std::shared_ptr<GameObject>(this), _pos, _rot);
  if (_parent != nullptr)
  {
    parent = (*_parent);
  }
}