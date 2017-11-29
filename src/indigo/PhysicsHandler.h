#ifndef __IND_PHYSICS_HANDLER__
#define __IND_PHYSICS_HANDLER__

#include <memory>
#include <vector>
#include <list>

namespace Indigo
{
  class RB;
  struct Contact;

  class PhysicsHandler
  {
    friend class Engine;
  public:
    void BroadPhase();
    void NarrowPhase();

    void Integrate();

    static void RegisterRB(std::weak_ptr<RB> _rb);
    static void _RegisterContact(std::weak_ptr<Contact> _contact);

  private:
    static std::list< std::weak_ptr<RB> > bodies;

    struct PossibleCol
    {
      std::weak_ptr<RB> l;
      std::weak_ptr<RB> r;
    };
    std::vector<PossibleCol> posCol;

    static std::vector< std::shared_ptr<Contact> > contacts;
    //Iterates contact resolution techniques over contacts vec
    void ResolveContacts();
  };
}

#endif