#include "ContactResolver.h"

#include "PhysicsHandler.h"
#include "RB.h"
#include "Collider.h"

#include <glm/glm.hpp>

using namespace Indigo;

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

}
void ContactResolver::AdjPosition(std::shared_ptr<Contact> _contact)
{

}
void ContactResolver::AdjVelocity(std::shared_ptr<Contact> _contact)
{

}