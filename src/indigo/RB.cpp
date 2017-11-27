#include "RB.h"

#include "GameObject.h"

using namespace Indigo;

void RB::onCreation()
{
  //Register to physics handler here
}

void RB::onUpdate()
{

}

void RB::AssignCollider(ColliderType _type)
{
  std::shared_ptr<Collider> newCol = std::make_shared<Collider>();

  //Create collider of _type and send to
  //_AssignCollider to do lower-level stuff
  switch (_type)
  {
  case Box:
    newCol->type = ColliderType::Box;
    break;
  case Sphere:
    newCol->type = ColliderType::Sphere;
    break;
  case Capsule:
    newCol->type = ColliderType::Capsule;
  default:

    break;
  }

  _AssignCollider(newCol);
}
void RB::ColliderResize(float _size)
{
  collider->size = _size;
}
void RB::ColliderRePosition(glm::vec3 _pos)
{
  collider->centerPos = _pos;
}

void RB::_AssignCollider(std::weak_ptr<Collider> _col)
{
  collider.reset();

  collider = _col.lock();
  collider->parent = parent.lock()->GetComponent<RB>();
}

void RB::RegCollision(std::weak_ptr<RB> _other)
{
  std::shared_ptr<Collision> c = std::make_shared<Collision>();
  c->thisRB = parent.lock()->GetComponent<RB>();
  c->otherRB = _other;
  //TODO
  c->hitPoint = glm::vec3(0);

  //Calling onCollision for GO that will call it on all components
  parent.lock()->onCollision(c);
}