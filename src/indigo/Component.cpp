#include "Component.h"

#include "GameObject.h"

using namespace Indigo;

void Component::ParentTo(std::weak_ptr<GameObject> _go)
{
  //Changing parent weak_ptr to have access to shared_ptr
  //that _go has access to
  parent = _go.lock();
  transform = parent->transform;
}