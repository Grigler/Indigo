#include "ContactResolver.h"

#include "PhysicsHandler.h"
#include "RB.h"
#include "Collider.h"

#include "Application.h"
#include "Transform.h"

using namespace Indigo;

//This is the number of iterations that PhysX uses
//http://www.richardtonge.com/presentations/Tonge-2012-GDC-solvingRigidBodyContacts.pdf
int ContactResolver::lcpIterations = 4;

void ContactResolver::ResolveContacts(std::vector< std::shared_ptr<Contact> > &_contacts)
{
  for (auto c = _contacts.begin(); c != _contacts.end(); c++)
  {
    //Adjust Positions to fix interpenetrations
    AdjPosition((*c));

    //Adjust velocities to resolve contact
    AdjVelocity((*c));
  }

  _contacts.clear();
}

void ContactResolver::AdjPosition(std::shared_ptr<Contact> _contact)
{
  //Basic linear projection - does not handle angular components
  glm::vec3 lVel = _contact->thisRB.lock()->linearVel;
  glm::vec3 rVel = _contact->otherRB.lock()->linearVel;
  glm::vec3 norm = _contact->contactNorm;

  float invMassL = 1.0f / _contact->thisRB.lock()->mass;
  float invMassR = 1.0f / _contact->otherRB.lock()->mass;

  glm::vec3 relVel = lVel - rVel;

  float linear = glm::dot(lVel - rVel, norm) / (invMassL + invMassR);
  //printf("linear: %f\n", linear);
  float magL = invMassL * _contact->penetrationDepth * linear;
  float magR = invMassR * _contact->penetrationDepth * linear;
  printf("RelVel: %f\n", glm::length(relVel));
  if (glm::length(relVel) >= 2.0f)
  {
    magL *= (0.9f*Application::GetFixedDT());
    magR *= (0.9f*Application::GetFixedDT());
  }

  _contact->thisRB.lock()->transform.lock()->MoveDir(-norm, magL);
  _contact->otherRB.lock()->transform.lock()->MoveDir(norm, magR);

  _contact->contactPoint += (norm*magL) + (norm*magR);
}
void ContactResolver::AdjVelocity(std::shared_ptr<Contact> _contact)
{
  glm::vec3 lVel = _contact->thisRB.lock()->linearVel;
  glm::vec3 rVel = _contact->otherRB.lock()->linearVel;

  glm::vec3 lVelA = _contact->thisRB.lock()->angularVel;
  glm::vec3 rVelA = _contact->otherRB.lock()->angularVel;

  float lMass = _contact->thisRB.lock()->mass;
  float rMass = _contact->otherRB.lock()->mass;

  glm::vec3 norm = _contact->contactNorm;

  float restitution = 0.75f; //Todo - pull from physics material

  //Used in both linear and angular calculations - so cache it
  float relVelProj = -(1.0f + restitution)*glm::dot(lVel - rVel, norm);
  //Magnitude of linear momentum
  float linear = relVelProj / ((1.0f / lMass) + (1.0f / rMass));

  relVelProj = -(1.0f + restitution)*glm::dot(lVelA - rVelA, norm);

  //Bookkeeping for angular
  glm::mat3 inverseInertiaL = _contact->thisRB.lock()->GetInverseInertiaTensor();
  glm::mat3 inverseInertiaR = _contact->otherRB.lock()->GetInverseInertiaTensor();
  glm::vec3 torqueArmL = _contact->contactPoint -
    _contact->thisRB.lock()->transform.lock()->GetPosition();
  glm::vec3 torqueArmR = _contact->contactPoint -
    _contact->otherRB.lock()->transform.lock()->GetPosition();

  float angular = relVelProj;
  angular *= glm::dot(norm, glm::cross(glm::cross(torqueArmL, norm)*inverseInertiaL, torqueArmL)) +
    glm::dot(norm, glm::cross(glm::cross(torqueArmR, norm)*inverseInertiaR, torqueArmR));

  float magnitude = linear + angular;

  _contact->thisRB.lock()->linearVel += (magnitude*norm) / lMass;
  _contact->thisRB.lock()->angularVel += glm::cross(torqueArmL, magnitude*norm)*inverseInertiaL;

  _contact->otherRB.lock()->linearVel += (-magnitude*norm) / rMass;
  _contact->otherRB.lock()->angularVel += glm::cross(torqueArmR, -magnitude*norm)*inverseInertiaR;
}

void ContactResolver::ResolveContactsLCP(std::vector< std::shared_ptr<Contact> > &_contacts)
{
  std::vector<CImpulsePair> contacts;
  contacts.reserve(_contacts.size());
  for (auto c = _contacts.begin(); c != _contacts.end(); c++)
  {
    CImpulsePair p;
    p.c = (*c);
    p.impulse = 0.0f;
    p.hasSwitched = false;
    contacts.push_back(p);
  }

  float scaling = (0.8f / Application::GetFixedDT());

  for (int i = 0; i < 4; i++)
  {
    for (auto p = contacts.begin(); p != contacts.end(); p++)
    {
      //Adjust velocities to resolve contact
      p->impulse = GetVelocityLCP((*p), (*p).impulse);
    }
  }

  //ApplyImpulses(contacts);

  _contacts.clear();

  /*
  for (int iteration = 0; iteration < lcpIterations; iteration++)
  {
      for (auto p = contacts.begin(); p != contacts.end(); p++)
      {
        std::shared_ptr<Contact> c = (*p).c;
        //Seperating the 6x6 mass matrix into a mass block and inertia tensor block
        glm::mat3 invMassBlock = glm::mat3(1.0f / c->thisRB.lock()->mass);
        glm::mat3 invInertiaBlock = c->thisRB.lock()->GetInverseInertiaTensor();

        glm::vec3 arm = c->thisRB.lock()->transform.lock()->GetPosition() -
          c->contactPoint;

        glm::vec3 jNorm = c->contactNorm;
        glm::vec3 jArm = glm::cross(arm, jNorm);

        glm::vec3 mMass = jNorm * invMassBlock * glm::transpose(invMassBlock);
        glm::vec3 mInertia = jArm * invInertiaBlock * glm::transpose(invInertiaBlock);;

        glm::vec3 impulse;

        //Keeping positive
        //p->impulse = glm::max(0.0f, p->impulse);
      }
  }

  _contacts.clear();
  */
}

float ContactResolver::GetVelocityLCP(CImpulsePair &_p, float _mag)
{
  std::shared_ptr<Contact> _contact = _p.c;

  glm::vec3 lVel = _contact->thisRB.lock()->linearVel;
  glm::vec3 rVel = _contact->otherRB.lock()->linearVel;

  glm::vec3 lVelA = _contact->thisRB.lock()->angularVel;
  glm::vec3 rVelA = _contact->otherRB.lock()->angularVel;

  float lMass = _contact->thisRB.lock()->mass;
  float rMass = _contact->otherRB.lock()->mass;

  glm::vec3 norm = _contact->contactNorm;

  float restitution = 0.75f; //Todo - pull from physics material

                             //Used in both linear and angular calculations - so cache it
  float relVelProj = -(1.0f + restitution)*glm::dot(lVel - rVel, norm);
  //Magnitude of linear momentum
  float linear = relVelProj / ((1.0f / lMass) + (1.0f / rMass));

  relVelProj = -(1.0f + restitution)*glm::dot(lVelA - rVelA, norm);

  //Bookkeeping for angular
  glm::mat3 inverseInertiaL = _contact->thisRB.lock()->GetInverseInertiaTensor();
  glm::mat3 inverseInertiaR = _contact->otherRB.lock()->GetInverseInertiaTensor();
  glm::vec3 torqueArmL = _contact->contactPoint -
    _contact->thisRB.lock()->transform.lock()->GetPosition();
  glm::vec3 torqueArmR = _contact->contactPoint -
    _contact->otherRB.lock()->transform.lock()->GetPosition();

  float angular = relVelProj;
  angular *= glm::dot(norm, glm::cross(glm::cross(torqueArmL, norm)*inverseInertiaL, torqueArmL)) +
    glm::dot(norm, glm::cross(glm::cross(torqueArmR, norm)*inverseInertiaR, torqueArmR));

  float mult = 1.0f;
  if (glm::dot(torqueArmL, norm) >= 0.0f)
  {
    _p.hasSwitched = true;
    //mult = -1.0f;
  }

  float preMag = _mag;

  _mag -= (linear + angular)*mult;

  _mag = glm::max(0.0f, _mag);
  float deltaMag = glm::max(0.0f, _mag) - preMag; 
  //deltaMag *= mult;
  printf("\nPreMag: %f\nMag: %f\nDMag: %f\n", preMag, _mag, deltaMag);

  //_p.dv += (deltaMag*norm) / lMass;
  //_p.dav += glm::cross(torqueArmL, deltaMag*norm)*inverseInertiaL;

  _contact->thisRB.lock()->linearVel += (deltaMag*norm) / lMass;
  _contact->thisRB.lock()->angularVel += glm::cross(torqueArmL, deltaMag*norm)*inverseInertiaL;
  
  _contact->otherRB.lock()->linearVel += (-deltaMag*norm) / rMass;
  _contact->otherRB.lock()->angularVel += glm::cross(torqueArmR, -deltaMag*norm)*inverseInertiaR;

  return _mag;
}
void ContactResolver::ApplyImpulses(std::vector<CImpulsePair> &_pairs)
{
  for (auto p = _pairs.begin(); p != _pairs.end(); p++)
  {
    std::shared_ptr<Contact> c = p->c;

    glm::vec3 norm = c->contactNorm;

    glm::vec3 torqueArmL = c->contactPoint -
      c->thisRB.lock()->transform.lock()->GetPosition();
    glm::vec3 torqueArmR = c->contactPoint -
      c->otherRB.lock()->transform.lock()->GetPosition();

    glm::mat3 inverseInertiaL = c->thisRB.lock()->GetInverseInertiaTensor();
    glm::mat3 inverseInertiaR = c->otherRB.lock()->GetInverseInertiaTensor();

    if (p->hasSwitched) p->impulse *= -1.0f;

    c->thisRB.lock()->linearVel += (p->impulse*norm) / c->thisRB.lock()->mass;
    c->thisRB.lock()->angularVel += glm::cross(torqueArmL, p->impulse*norm)*inverseInertiaL;

    c->otherRB.lock()->linearVel += (-p->impulse*norm) / c->otherRB.lock()->mass;
    c->otherRB.lock()->angularVel += glm::cross(torqueArmR, -p->impulse*norm)*inverseInertiaR;
  }
}