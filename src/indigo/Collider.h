#ifndef __IND_COLLIDER__
#define __IND_COLLIDER__

#include <memory>

#include <glm/glm.hpp>

namespace Indigo
{
  //Bitfield for easy | collider type checking
#define COL_TYPE_BOX     0b001
#define COL_TYPE_SPHERE  0b010
#define COL_TYPE_CAPSULE 0b100

  enum ColliderType : unsigned char
  {
    Box = COL_TYPE_BOX,
    Sphere = COL_TYPE_SPHERE,
    Capsule = COL_TYPE_CAPSULE
  };

  class RB;
  class Transform;

  class Collider
  {
  public:
    std::weak_ptr<RB> parent;
    std::weak_ptr<Transform> transform;

    ColliderType type;

    //Evaluates type of both colliders and calls appropriate
    //collision test function
    bool CheckCol(std::weak_ptr<Collider> _against);

    //Defined in local space - tranformed by Model Matrix in col check
    glm::vec3 offset;
    float size;

  private:

    bool BoxBox(std::weak_ptr<Collider> _against);
    bool SphereSphere(std::weak_ptr<Collider> _against);
    bool BoxSphere(std::weak_ptr<Collider> _against);
    //TODO - Capsule stuff

  };
}

#endif