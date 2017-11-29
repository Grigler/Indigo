#include "PhysicsHandler.h"

#include "RB.h"
#include "Collider.h"
#include "AABB.h"

#include "ContactResolver.h"

#include "Application.h"

using namespace Indigo;

std::list< std::weak_ptr<RB> > PhysicsHandler::bodies;
std::vector< std::shared_ptr<Contact> > PhysicsHandler::contacts;

void PhysicsHandler::BroadPhase()
{
  posCol.clear();
  //AABB check all bodies in bodies
  for (auto i = bodies.begin(); i != bodies.end(); i++)
  {
    
    for (auto j = i; j != bodies.end(); j++)
    {
      if (i != j)
      {
        if (AABB::Test((*i).lock()->aabb, (*j).lock()->aabb))
        {
          PossibleCol pc;
          pc.l = (*i); pc.r = (*j);
          posCol.push_back(pc);
        }
      }
    }
  }
}
void PhysicsHandler::NarrowPhase()
{
  //Narrowphase check
  for (auto i = posCol.begin(); i != posCol.end(); i++)
  {
    PossibleCol c = (*i);
    //This will call other onCollision event functions
    //Also registers contacts in contacs vec for resolving later
    c.l.lock()->collider->CheckCol(c.r.lock()->collider);
  }

  ResolveContacts();
}

void PhysicsHandler::Integrate()
{
  for (auto i = bodies.begin(); i != bodies.end(); i++)
  {
    (*i).lock()->Integrate();
  }
}

void PhysicsHandler::RegisterRB(std::weak_ptr<RB> _rb)
{
  bodies.push_back(_rb);
}
void PhysicsHandler::_RegisterContact(std::weak_ptr<Contact> _contact)
{
  contacts.push_back(_contact.lock());
}

void PhysicsHandler::ResolveContacts()
{
  ContactResolver::ResolveContacts(contacts);
}
