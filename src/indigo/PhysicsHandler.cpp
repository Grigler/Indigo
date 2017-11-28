#include "PhysicsHandler.h"

#include "RB.h"
#include "Collider.h"
#include "AABB.h"

#include "Application.h"

using namespace Indigo;

std::list< std::weak_ptr<RB> > PhysicsHandler::bodies;

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
    //Also registers the collision in the cols vector
    c.l.lock()->collider->CheckCol(c.r.lock()->collider);
  }

  //Resolving collision contacts
  for (auto i = cols.begin(); i != cols.end(); i++)
  {
    ResolveCollision((*i));
  }

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
void PhysicsHandler::_RegisterCollision(std::weak_ptr<Collision> _col)
{
  cols.push_back(_col.lock());
}

void PhysicsHandler::ResolveCollision(std::weak_ptr<Collision> _col)
{
 
}