#ifndef __IND_RIGID_BODY__
#define __IND_RIGID_BODY__

#include <memory>

#include <glm/glm.hpp>

#include "Component.h"
#include "Collider.h"

namespace Indigo
{
  struct Collision
  {
    std::weak_ptr<RB> thisRB;
    std::weak_ptr<RB> otherRB;
    glm::vec3 hitPoint;
    glm::vec3 hitNorm;
  };

  class AABB;

  //TODO - FORCES

  class RB : public Component
  {
    friend class Collider;
    friend class PhysicsHandler;

  public:
    //Register the RB component with physics handler
    void onCreation();

    //Interface function to change collider type by enum
    void AssignCollider(ColliderType _type);
    void ColliderResize(float _size);
    void ColliderSetOffset(glm::vec3 _offset);

    //Force Stuff
    void ApplyForceAtLocation(glm::vec3 _force, glm::vec3 _loc);
    void ApplyTorque(glm::vec3 _torque);

    glm::vec3 GetLinearVel() { return linearVel; }
    glm::vec3 GetAngularVel() { return angularVel; }

    void SetGravity(bool _to) { isGravityOn = _to; }
  private:
    //Not sure if this function is entirely necessary
    void onUpdate();

    void Integrate();
    glm::vec3 linearVel;
    glm::vec3 linearAccel;
    glm::vec3 force;

    glm::vec3 angularVel;
    glm::vec3 torque;

    float mass;
    float drag;
    bool isGravityOn;
    glm::mat3 inertiaTensor;

    //Lower-level function, called by interface func, to handle
    //collider change at a lower-level
    void _AssignCollider(std::weak_ptr<Collider> _col);
    std::shared_ptr<Collider> collider;

    //If a RB exists, it must have a mesh - so pull from Mesh
    std::shared_ptr<AABB> aabb;

    //Called by collider when collision is detected
    void RegCollision(std::weak_ptr<RB> _other);
    void RegCollision(std::weak_ptr<Collision> _col);
  };
}

#endif