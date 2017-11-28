#ifndef __IND_PHYSICS_HANDLER__
#define __IND_PHYSICS_HANDLER__

#include <memory>
#include <vector>
#include <list>

namespace Indigo
{
  class RB;
  struct Collision;

  class PhysicsHandler
  {
    friend class Engine;
  public:
    void BroadPhase();
    void NarrowPhase();

    void Integrate();

    static void RegisterRB(std::weak_ptr<RB> _rb);
    static void _RegisterCollision(std::weak_ptr<Collision> _col);

  private:
    static std::list< std::weak_ptr<RB> > bodies;

    struct PossibleCol
    {
      std::weak_ptr<RB> l;
      std::weak_ptr<RB> r;
    };
    std::vector<PossibleCol> posCol;

    static std::vector< std::shared_ptr<Collision> > cols;
    void ResolveCollision(std::weak_ptr<Collision> _col);
  };
}

#endif