#include "Collider.h"

#include "RB.h"

using namespace Indigo;

bool Collider::CheckCol(std::weak_ptr<Collider> _against)
{
  unsigned int bitField = type | _against.lock()->type;

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
    break;
  }

  if (hit)
  {
    parent.lock()->RegCollision(_against.lock()->parent);
  }


  return hit;
}

//TODO - make it return a hitvec too
bool Collider::BoxBox(std::weak_ptr<Collider> _against)
{

  return false;
}
bool Collider::SphereSphere(std::weak_ptr<Collider> _against)
{

  return false;
}
bool Collider::BoxSphere(std::weak_ptr<Collider> _against)
{

  return false;
}