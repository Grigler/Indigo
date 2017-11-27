#include "RB.h"

#include "PhysicsHandler.h"
#include "Collider.h"

#include "GameObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"


using namespace Indigo;

void RB::onCreation()
{
  //Register to physics handler here
  PhysicsHandler::RegisterRB(parent.lock()->GetComponent<RB>());

  //Creating a default collider box
  collider = std::make_shared<Collider>();
  collider->type = ColliderType::Box;
  collider->offset = glm::vec3(0);
  collider->size = 1.0f;

  //Getting a local shared_ptr to aabb defined and updated in mesh
  aabb = parent.lock()->GetComponent<MeshRenderer>().lock()->mesh->aabb;
}

void RB::onUpdate()
{
  //Do I even need this function?
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
void RB::ColliderSetOffset(glm::vec3 _offset)
{
  collider->offset = _offset;
}

void RB::_AssignCollider(std::weak_ptr<Collider> _col)
{
  collider.reset();

  collider = _col.lock();
  collider->parent = parent.lock()->GetComponent<RB>();
  collider->transform = transform;
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