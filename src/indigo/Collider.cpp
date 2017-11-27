#include "Collider.h"

#include "GameObject.h"
#include "Transform.h"
#include "RB.h"

#include "Application.h"

//Used for easy square distance function
#include <glm/gtx/norm.hpp>

using namespace Indigo;

bool Collider::CheckCol(std::weak_ptr<Collider> _against)
{
  unsigned char bitField = type | _against.lock()->type;

  //Note: Identical types could be directly compared to bitfield
  //but have been left in this form for readability
  bool hit = false;


  switch (bitField)
  {
  case (COL_TYPE_BOX | COL_TYPE_BOX):
    hit = BoxBox(_against);
    break;
  case (COL_TYPE_BOX | COL_TYPE_SPHERE):
    hit = BoxSphere(_against);
    break;
  case (COL_TYPE_BOX | COL_TYPE_CAPSULE):
    //TODO
    break;
  case (COL_TYPE_SPHERE | COL_TYPE_SPHERE):
    hit = SphereSphere(_against);
    break;
  case (COL_TYPE_SPHERE | COL_TYPE_CAPSULE):
    //TODO
    break;
  case (COL_TYPE_CAPSULE | COL_TYPE_CAPSULE):
    //TODO
    break;
  default:
    //COLLIDER TYPE DOES NOT EXIST
    Application::ErrPrint(std::exception("Collider type does not exist"));
    break;
  }

  if (hit)
  {
    parent.lock()->RegCollision(_against.lock()->parent);
  }


  return hit;
}

//TODO - make it return a hitvec too
//This should work as an OBB-OBB test, but I'm currently just doing a basic AABB-AABB test
bool Collider::BoxBox(std::weak_ptr<Collider> _against)
{
  //Transforming position by modelmatrix to give WS coords
  glm::vec3 a = glm::vec4(1.0f) * transform.lock()->GetModelMatWithOffset(offset);
  glm::vec3 b = glm::vec4(1.0f) *
    _against.lock()->transform.lock()->GetModelMatWithOffset(_against.lock()->offset);

  float r = _against.lock()->size + size;

  if (glm::abs(a.x - b.x) > r) return false;
  if (glm::abs(a.y - b.y) > r) return false;
  if (glm::abs(a.z - b.z) > r) return false;

  //Registering hit
  parent.lock()->RegCollision(_against.lock()->parent);

  return true;
}
bool Collider::SphereSphere(std::weak_ptr<Collider> _against)
{
  //Transforming position by modelmatrix to give WS coords
  glm::vec3 transPos = glm::vec4(1.0f) * transform.lock()->GetModelMatWithOffset(offset);
  glm::vec3 otherTransPos = glm::vec4(1.0f) *
    _against.lock()->transform.lock()->GetModelMatWithOffset(_against.lock()->offset);

  //Comparing square distance with (rad1+rad2)^2
  if (glm::distance2(transPos, otherTransPos) <= (size + _against.lock()->size)*(size + _against.lock()->size))
  {
    //Registering hit
    parent.lock()->RegCollision(_against.lock()->parent);
    return true;
  }
  else
  {
    return false;
  }
}
bool Collider::BoxSphere(std::weak_ptr<Collider> _against)
{
  //Transforming position by modelmatrix to give WS coords
  glm::vec3 transPos = glm::vec4(1.0f) * transform.lock()->GetModelMatWithOffset(offset);
  glm::vec3 otherTransPos = glm::vec4(1.0f) *
    _against.lock()->transform.lock()->GetModelMatWithOffset(_against.lock()->offset);



  return false;
}