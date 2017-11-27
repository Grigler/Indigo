/*
#ifndef __IND_PHYSICS_SPACE__
#define __IND_PHYSICS_SPACE__

#include <vector>
#include <memory>

namespace Indigo
{
  class AABB;
  class GameObject;

  //AABB-GO pair for broadphase world representation
  struct WorldEntry
  {
    std::weak_ptr<AABB> bv;
    std::weak_ptr<GameObject> parent;
    WorldEntry(std::weak_ptr<AABB> _bv, std::weak_ptr<GameObject> _parent)
    {
      bv = _bv;
      parent = _parent;
    }
  };

  //Used to hold possible collision pairs for narrowphase
  struct PossibleCol
  {
    std::weak_ptr<GameObject> l;
    std::weak_ptr<GameObject> r;
    PossibleCol(WorldEntry _l, WorldEntry _r)
    {
      l = _l.parent;
      r = _r.parent;
    }
  };
  
  struct Collision
  {
    //Collider and hit information
  };

  class PhysicsSpace
  {
    friend class Engine;
  public:
    static void Register(WorldEntry _this);

  private:
    //TODO - Change to spatially partitioned world view
    static std::vector<WorldEntry> world;

    static void Update();

    static void BroadPhase();
    static std::vector<Collision> NarrowPhase(std::vector<PossibleCol> &_ls);
  };
}

#endif
*/