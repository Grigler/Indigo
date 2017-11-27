#ifndef __IND_COLLIDER__
#define __IND_COLLIDER__

#include <memory>

#include <glm/glm.hpp>

namespace Indigo
{
  //Bitfield for easy | collider type checking
#define COL_TYPE_BOX     0x001
#define COL_TYPE_SPHERE  0x010
#define COL_TYPE_CAPSULE 0x100

  enum ColliderType
  {
    Box = COL_TYPE_BOX,
    Sphere = COL_TYPE_SPHERE,
    Capsule = COL_TYPE_CAPSULE
  };

  class RB;

  class Collider
  {
  public:
    std::weak_ptr<RB> parent;

    ColliderType type;

    //Evaluates type of both colliders and calls appropriate
    //collision test function
    bool CheckCol(std::weak_ptr<Collider> _against);

    glm::vec3 centerPos;
    float size;

  private:

    bool BoxBox(std::weak_ptr<Collider> _against);
    bool SphereSphere(std::weak_ptr<Collider> _against);
    bool BoxSphere(std::weak_ptr<Collider> _against);
    //TODO - Capsule stuff

  };
}

#endif