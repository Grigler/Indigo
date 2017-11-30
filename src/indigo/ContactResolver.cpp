#include "ContactResolver.h"

#include "PhysicsHandler.h"
#include "RB.h"
#include "Collider.h"

#include "Transform.h"

using namespace Indigo;

//HEAVILY BASED OFF OF https://github.com/idmillington/cyclone-physics/blob/master/src/contacts.cpp

//Resolves a given vector of contacts using non-linear projection
void ContactResolver::ResolveContacts(std::vector< std::shared_ptr<Contact> > &_contacts)
{
  printf("Contacts: %i\n", _contacts.size());

  for (auto c = _contacts.begin(); c != _contacts.end(); c++)
  {
    //Adjust Positions to fix interpenetrations
    //AdjPosition((*c));

    //Adjust velocities to resolve contact
    AdjVelocity((*c));
  }

  _contacts.clear();
}

void ContactResolver::CalcInternals(std::shared_ptr<Contact> _contact)
{
  //Calculate contact basis
  glm::mat3 contactBasis = GetContactBasis(_contact);

  //storing relative contact point for each body


  //Caluclating relative velocity at contact point


  //Calculate desired delta velocity for resolution

}
void ContactResolver::AdjPosition(std::shared_ptr<Contact> _contact)
{
  if (glm::abs(_contact->penetrationDepth) > 0.0f)
  {
    glm::vec3 toOther = glm::normalize(_contact->thisRB.lock()->transform.lock()->GetPosition() -
      _contact->otherRB.lock()->transform.lock()->GetPosition());
    
    float dirChange;
    glm::dot(toOther, _contact->contactNorm) > 0.0f ? dirChange = -1.0f : dirChange = 1.0f;

    if (_contact->thisRB.lock()->collider->type != ColliderType::Plane)
    {
      //SolvePenetration(_contact->penetrationDepth, _contact->contactNorm*dirChange, _contact->thisRB);
    }
    if (_contact->otherRB.lock()->collider->type != ColliderType::Plane)
    {
      //SolvePenetration(_contact->penetrationDepth, _contact->contactNorm*dirChange, _contact->otherRB);
    }

  }
}
void ContactResolver::AdjVelocity(std::shared_ptr<Contact> _contact)
{
  glm::vec3 lVel = _contact->thisRB.lock()->linearVel;
  glm::vec3 rVel = _contact->otherRB.lock()->linearVel;

  float lMass = _contact->thisRB.lock()->mass;
  float rMass = _contact->otherRB.lock()->mass;

  glm::vec3 norm = _contact->contactNorm;
  glm::vec3 pos = _contact->contactPoint;
  float restitution = 1.0f; //Todo - pull from physics material

  //Used in both linear and angular calculations - so cache it
  float relVelProj = ((-(1 + restitution))*glm::dot(lVel - rVel, norm));
  //Magnitude of linear momentum
  float linear = relVelProj / ((1.0f / lMass) + (1.0f / rMass));

  //Bookkeeping for angular
  glm::mat3 inverseInertiaL = _contact->thisRB.lock()->GetInverseInertiaTensor();
  glm::mat3 inverseInertiaR = _contact->otherRB.lock()->GetInverseInertiaTensor();
  glm::vec3 torqueArmL = _contact->contactPoint -
    _contact->thisRB.lock()->transform.lock()->GetPosition();
  glm::vec3 torqueArmR = _contact->contactPoint -
    _contact->otherRB.lock()->transform.lock()->GetPosition();

  float angular = 0.0f;//relVelProj;
  //angular *= glm::dot(norm, glm::cross(glm::cross(torqueArmL, norm)*inverseInertiaL, torqueArmL))
  //  + glm::dot(norm, glm::cross(glm::cross(torqueArmR, norm)*inverseInertiaR, torqueArmR));

  float magnitude = linear + angular;

  if(_contact->thisRB.lock()->collider->type != ColliderType::Plane)
    _contact->thisRB.lock()->linearVel += (magnitude*norm) / lMass;

  if (_contact->otherRB.lock()->collider->type != ColliderType::Plane)
   _contact->otherRB.lock()->linearVel += (-magnitude*norm) / rMass;
}

glm::mat3 ContactResolver::GetContactBasis(std::shared_ptr<Contact> _contact)
{
  glm::vec3 contactTangents[2];

  glm::vec3 n = _contact->contactNorm;

  //Checking for closest axis to z
  //X is closest axis
  if (glm::abs(_contact->contactNorm.x) > glm::abs(_contact->contactNorm.y))
  {
    float s = glm::inversesqrt(n.z*n.z + n.x*n.x);

    contactTangents[0] = glm::vec3(n.z*s, 0.0f, -n.x*s);

    contactTangents[1] = glm::vec3(n.y*contactTangents[0].x,
      n.z*contactTangents[0].x - n.x*contactTangents[0].z,
      -n.y*contactTangents[0].x);
  }
  else //Y is closest axis
  {
    float s = glm::inversesqrt(n.z*n.z + n.y*n.y);

    contactTangents[0] = glm::vec3(0.0f, -n.z*s, n.y*s);

    contactTangents[1] = glm::vec3(n.y*contactTangents[0].z - n.z*contactTangents[0].y,
      -n.x*contactTangents[0].z,
      n.x*contactTangents[0].y);
  }

  glm::mat3 contactBasis = glm::mat3(n, contactTangents[0], contactTangents[1]);

  return contactBasis;
}