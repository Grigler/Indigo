#ifndef __IND_RIGID_BODY__
#define __IND_RIGID_BODY__

#include <memory>

#include <glm/glm.hpp>

#include "Component.h"
#include "Collider.h"

namespace Indigo
{
  //TODO
  struct Collision
  {
    std::weak_ptr<RB> thisRB;
    std::weak_ptr<RB> otherRB;
    glm::vec3 hitPoint;
  };

  class RB : public Component
  {
    friend class Collider;
    //friend class PhysicsHandler; <-- for accessing col type
  public:
    //Register the RB component with physics handler
    void onCreation();
    //Check if it is deemed as colliding?
    void onUpdate();
    //Interface function to change collider type by enum
    void AssignCollider(ColliderType _type);
    void ColliderResize(float _size);
    void ColliderSetOffset(glm::vec3 _offset);

  private:
    //Lower-level function, called by interface func, to handle
    //collider change at a lower-level
    void _AssignCollider(std::weak_ptr<Collider> _col);
    std::shared_ptr<Collider> collider;

    //Called by collider when collision is detected
    void RegCollision(std::weak_ptr<RB> _other);
  };
}

#endif