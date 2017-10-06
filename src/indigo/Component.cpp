#include "Component.h"

using namespace Indigo;

Component::Component(std::shared_ptr<GameObject> _parent)
{
  parent = _parent;
}