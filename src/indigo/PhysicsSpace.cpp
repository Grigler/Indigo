#include "PhysicsSpace.h"

#include "AABB.h"
#include "GameObject.h"

using namespace Indigo;

std::vector<WorldEntry> PhysicsSpace::world;

void PhysicsSpace::Register(WorldEntry _this)
{
  world.push_back(_this);
}

void PhysicsSpace::Update()
{
  //Update positions

  //Check for collisions (Also calls narrow phase)
  BroadPhase();
}

void PhysicsSpace::BroadPhase()
{
  std::vector<PossibleCol> ls;
  
  //Check for AABB collisions to populate ls
  for (size_t i = 0; i < world.size(); i++)
  {
    for (size_t j = i+1; j < world.size(); j++)
    {
      if (AABB::Test(world.at(i).bv, world.at(j).bv))
      {
        ls.push_back(PossibleCol(world.at(i), world.at(j)));
      }
    }
  }

  printf("Size: %i\n", ls.size());

  NarrowPhase(ls);
}
std::vector<Collision> PhysicsSpace::NarrowPhase(std::vector<PossibleCol> &_ls)
{
  std::vector<Collision> cols;

  //Find colliders in each Possible col and check collision


  return cols;
}