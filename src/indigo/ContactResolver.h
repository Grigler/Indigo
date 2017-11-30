#ifndef __IND_CONTACT_RESOLVER__
#define __IND_CONTACT_RESOLVER__

#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace Indigo
{
  struct Contact;

  class ContactResolver
  {
    //Everything private as only the PhysicsHandler should
    //have access to anything here
    friend class PhysicsHandler;
  private:
    static void ResolveContacts(std::vector< std::shared_ptr<Contact> > &_contacts);

    static void CalcInternals(std::shared_ptr<Contact> _contact);
    static void AdjPosition(std::shared_ptr<Contact> _contact);
    static void AdjVelocity(std::shared_ptr<Contact> _contact);

    static glm::mat3 GetContactBasis(std::shared_ptr<Contact> _contact);
  };
}

#endif