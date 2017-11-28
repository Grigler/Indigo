#include "RB.h"

#include "PhysicsHandler.h"
#include "Collider.h"

#include "Application.h"
#include "GameObject.h"
#include "Transform.h"

#include "MeshRenderer.h"
#include "Mesh.h"

#include <glm/gtx/quaternion.hpp>

using namespace Indigo;

void RB::onCreation()
{
  //Register to physics handler here
  PhysicsHandler::RegisterRB(parent.lock()->GetComponent<RB>());

  //Creating a default collider box
  collider = std::make_shared<Collider>();
  collider->parent = parent.lock()->GetComponent<RB>();
  collider->transform = transform;

  collider->type = ColliderType::Sphere;
  collider->offset = glm::vec3(0);
  collider->size = 0.5f;

  //Getting a local shared_ptr to aabb defined and updated in mesh
  aabb = parent.lock()->GetComponent<MeshRenderer>().lock()->mesh->aabb;

  //Setting up force and accel values
  linearVel = glm::vec3(0);
  angularVel = glm::vec3(0);
  force = glm::vec3(0);
  torque = glm::vec3(0);
  mass = 5.0f;
  drag = 10.0f;
  isGravityOn = true;
  inertiaTensor = glm::mat3(1);
  //TODO - CURRENTLY HARD CODED FOR SPHERE
  inertiaTensor[0][0] = (mass * 0.4f)*(collider->size*collider->size);
  inertiaTensor[1][1] = (mass * 0.4f)*(collider->size*collider->size);
  inertiaTensor[2][2] = (mass * 0.4f)*(collider->size*collider->size);

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

void RB::ApplyForceAtLocation(glm::vec3 _force, glm::vec3 _loc)
{
  force += _force;
  
  glm::vec3 centMass = glm::vec3(0); //TODO get from collider
  glm::vec3 localFLocation = centMass - _loc;
  torque += glm::cross(localFLocation, _force);
}
void RB::ApplyTorque(glm::vec3 _torque)
{
  torque += _torque;
}

void RB::onUpdate()
{
  //Do I even need this function?
}
void RB::Integrate()
{
  //TODO - pass dt in as an argument, could be difference between
  //bodies.at(0) and bodies.at(bodies.size())

  //Storing dt at start of integration step
  float dt = glm::clamp(Application::GetDT(), 0.0001f, 0.016f);

  //Using forces to calculate a to get v
  glm::vec3 lastAccel = linearAccel + (force / mass);
  if (isGravityOn) lastAccel += glm::vec3(0.0f, -9.81f, 0.0f);
  linearVel += lastAccel * dt;

  //Calculating Angular Velocity from torque and inertia tensor
  glm::mat3 R = transform.lock()->GetRotationMat();
  glm::mat3 inertiaTensorInv = R*glm::inverse(inertiaTensor)*glm::transpose(R);
  angularVel += inertiaTensorInv*torque*dt;

  //Applying drag to linear and angular velocities
  linearVel *= (1 - dt * drag);
  angularVel *= (1 - dt * drag);

  //Applying linearVel and angularVel to position and rotation
  transform.lock()->MoveDir(linearVel, dt);
  transform.lock()->SetRotation(transform.lock()->GetRotation()+(angularVel*dt));

  //Resetting force and torque as these are impulses
  force = glm::vec3(0.0f);
  torque = glm::vec3(0.0f);
}

void RB::_AssignCollider(std::weak_ptr<Collider> _col)
{
  collider.reset();

  collider = _col.lock();
  collider->parent = parent.lock()->GetComponent<RB>();
  collider->transform = transform;
}

void RB::RegContact(std::weak_ptr<Contact> _contact)
{
  //Registering this component for onCollision func
  _contact.lock()->thisRB = parent.lock()->GetComponent<RB>();

  PhysicsHandler::_RegisterContact(_contact);

  parent.lock()->onCollision(_contact);
}