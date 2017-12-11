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
  case (COL_TYPE_SPHERE | COL_TYPE_PLANE):
    hit = SpherePlane(_against);
    break;
  case (COL_TYPE_SPHERE | COL_TYPE_CAPSULE):
    //TODO
    break;
  case (COL_TYPE_CAPSULE | COL_TYPE_CAPSULE):
    //TODO
    break;
  case (COL_TYPE_PLANE | COL_TYPE_PLANE): 

    break;
  default:
    //COLLIDER TYPE DOES NOT EXIST
    Application::ErrPrint(std::exception("Collider type does not exist"));
    break;
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
  //parent.lock()->RegContact(_against.lock()->parent);

  return true;
}
bool Collider::SphereSphere(std::weak_ptr<Collider> _against)
{
  //Transforming position by modelmatrix to give WS coords
  glm::vec3 transPos = transform.lock()->GetPosition();
  glm::vec3 otherTransPos = _against.lock()->transform.lock()->GetPosition();

  //Comparing square distance with (rad1+rad2)^2
  glm::vec3 midLine = transPos - otherTransPos;
  float d2 = glm::length2(midLine);
  if (d2 <= glm::pow((size + _against.lock()->size),2))
  { 
    float d = glm::sqrt(d2);
    glm::vec3 norm = midLine*(1.0f / d);

    std::shared_ptr<Contact> c = std::make_shared<Contact>();

    c->contactNorm = norm;
    c->contactPoint = transPos + (midLine*0.5f);
    c->contactOther = otherTransPos - (midLine*0.5f);
    c->penetrationDepth = (size + _against.lock()->size) - d;

    c->otherRB = _against.lock()->parent;

    parent.lock()->RegContact(c);
    return true;
  }
  else
  {
    return false;
  }
}
bool Collider::SpherePlane(std::weak_ptr<Collider> _against)
{
  std::weak_ptr<Collider> sphereCol;
  glm::vec3 spherePos;

  std::weak_ptr<Collider> planeCol;
  glm::vec3 planePos;
  if (type == COL_TYPE_PLANE)
  {
    planeCol = parent.lock()->collider;
    sphereCol = _against;
  }
  else
  {
    planeCol = _against;
    sphereCol = parent.lock()->collider;
  }

  spherePos = sphereCol.lock()->transform.lock()->GetPosition();
  planePos = planeCol.lock()->transform.lock()->GetPosition();

  glm::vec3 pNorm = planeCol.lock()->transform.lock()->GetRotationMat()*planeCol.lock()->_normal;

  float d = glm::dot(spherePos - planePos, pNorm);
  
  //printf("D: %f\n", d);
  if (d < sphereCol.lock()->size)
  {
    std::shared_ptr<Contact> c = std::make_shared<Contact>();

    c->contactNorm = pNorm;
    c->penetrationDepth = sphereCol.lock()->size - d;
    c->contactPoint = -pNorm * (d+sphereCol.lock()->size);

    c->otherRB = _against.lock()->parent;

    parent.lock()->RegContact(c);
    return true;
  }

  return false;
}
bool Collider::BoxSphere(std::weak_ptr<Collider> _against)
{
  //Transforming position by modelmatrix to give WS coords
  glm::vec3 transPos = glm::vec4(1.0f) * transform.lock()->GetModelMatWithOffset(offset);
  glm::vec3 otherTransPos = glm::vec4(1.0f) *
    _against.lock()->transform.lock()->GetModelMatWithOffset(_against.lock()->offset);



  return false;
}