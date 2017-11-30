#ifndef __IND_COLLIDER__
#define __IND_COLLIDER__

#include <memory>

#include <glm/glm.hpp>

namespace Indigo
{
  //Bitfield for easy | collider type checking
#define COL_TYPE_BOX     0b0001
#define COL_TYPE_SPHERE  0b0010
#define COL_TYPE_CAPSULE 0b0100
#define COL_TYPE_PLANE   0b1000

  enum ColliderType : unsigned char
  {
    Box = COL_TYPE_BOX,
    Sphere = COL_TYPE_SPHERE,
    Capsule = COL_TYPE_CAPSULE,
    Plane = COL_TYPE_PLANE
  };

  class RB;
  class Transform;

  class Collider
  {
    friend class PhysicsHandler;
  public:
    std::weak_ptr<RB> parent;
    std::weak_ptr<Transform> transform;

    ColliderType type;

    //Evaluates type of both colliders and calls appropriate
    //collision test function
    bool CheckCol(std::weak_ptr<Collider> _against);

    //Defined in local space - tranformed by Model Matrix in col check
    glm::vec3 offset;
    //Radius for sphere, uniform half-extents for box
    float size;
    //Only used by a plane collider
    glm::vec3 _normal;

  private:

    bool BoxBox(std::weak_ptr<Collider> _against);
    bool SphereSphere(std::weak_ptr<Collider> _against);
    bool SpherePlane(std::weak_ptr<Collider> _against);
    bool BoxSphere(std::weak_ptr<Collider> _against);
    //TODO - Capsule stuff

  };
}

#endif