#include "ContactResolver.h"

#include "PhysicsHandler.h"
#include "RB.h"
#include "Collider.h"

using namespace Indigo;

//HEAVILY BASED OFF OF https://github.com/idmillington/cyclone-physics/blob/master/src/contacts.cpp

//Resolves a given vector of contacts using non-linear projection
void ContactResolver::ResolveContacts(std::vector< std::shared_ptr<Contact> > &_contacts)
{
  for (auto c = _contacts.begin(); c != _contacts.end(); c++)
  {
    //Calculate internals for preperation
    CalcInternals((*c));

    //Adjust Positions for interpenetration
    AdjPosition((*c));

    //Adjust velocities for contact resolution
    AdjVelocity((*c));
  }
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
  //Iteratively resolving interpenetrations in order of severity


}
void ContactResolver::AdjVelocity(std::shared_ptr<Contact> _contact)
{
  //Iteratively handling impacts in order of severity


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