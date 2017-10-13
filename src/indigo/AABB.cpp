#include "AABB.h"

using namespace Indigo;

void AABB::Recalc(std::vector<glm::vec3> _verts)
{
  if (_verts.size() <= 0) return;

  glm::vec3 max = _verts.at(0);
  glm::vec3 min = _verts.at(0);

  //Starting from second vert
  for (auto i = ++_verts.begin(); i != _verts.end(); i++)
  {
    //Max
    max.x = std::fmaxf(max.x, i->x);
    max.y = std::fmaxf(max.y, i->y);
    max.z = std::fmaxf(max.z, i->z);
    //Min
    min.x = std::fminf(min.x, i->x);
    min.y = std::fminf(min.y, i->y);
    min.z = std::fminf(min.z, i->z);
  }
  //Calculating midPoint and size
  centerPos = (min + max) / 2.0f;
  //Dividing by 2.of as need the offset from the center
  offset = (glm::abs(max) - glm::abs(min)) / 2.0f;
}

//Dereferences this and calls static
bool AABB::Test(AABB _against)
{
  return AABB::Test(*this, _against);
}
//Static implementation
bool AABB::Test(AABB _a, AABB _b)
{
  //Using bools to cut down on branching
  bool x = std::fabs(_a.centerPos.x - _b.centerPos.x) <= (_a.offset.x + _b.offset.x);
  bool y = std::fabs(_a.centerPos.y - _b.centerPos.y) <= (_a.offset.y + _b.offset.y);
  bool z = std::fabs(_a.centerPos.z - _b.centerPos.z) <= (_a.offset.z + _b.offset.z);
  
  return x && y && z;
}

void AABB::SetScale(glm::vec3 _s)
{
  offset.x * _s.x;
  offset.y * _s.y;
  offset.z * _s.z;
}