#include "ContactResolver.h"

#include "PhysicsHandler.h"
#include "RB.h"
#include "Collider.h"

#include <glm/glm.hpp>

using namespace Indigo;

//HEAVILY BASED OFF OF https://github.com/idmillington/cyclone-physics/blob/master/src/contacts.cpp

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