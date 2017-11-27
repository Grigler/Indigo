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
  private:

    //Check if it is deemed as colliding?
    void onUpdate();

    //Lower-level function, called by interface func, to handle
    //collider change at a lower-level
    void _AssignCollider(std::weak_ptr<Collider> _col);
    std::shared_ptr<Collider> collider;

    //If a RB exists, it must have a mesh - so pull from Mesh
    std::shared_ptr<AABB> aabb;

    //Called by collider when collision is detected
    void RegCollision(std::weak_ptr<RB> _other);
  };
}

#endif