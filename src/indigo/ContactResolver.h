#ifndef __IND_CONTACT_RESOLVER__
#define __IND_CONTACT_RESOLVER__

#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace Indigo
{
  struct Contact;
  class RB;

  //Helper class used to encapsulate the contact resolution process
  //in  a single class
  class ContactResolver
  {
    //Everything private as only the PhysicsHandler should
    //have access to anything here
    friend class PhysicsHandler;
  private:
    //Working single-contact solver
    static void ResolveContacts(std::vector< std::shared_ptr<Contact> > &_contacts);

    static void AdjPosition(std::shared_ptr<Contact> _contact);
    static void AdjVelocity(std::shared_ptr<Contact> _contact);

    static int lcpIterations;
    static void ResolveContactsLCP(std::vector< std::shared_ptr<Contact> > &_contacts);
    struct CImpulsePair
    {
      std::shared_ptr<Contact> c;
      float impulse;
      bool hasSwitched;
      glm::vec3 dv;
      glm::vec3 dav;
    };

    static float GetVelocityLCP(CImpulsePair &_p, float _mag);
    static void ApplyImpulses(std::vector<CImpulsePair> &_pairs);
  };
}

#endif