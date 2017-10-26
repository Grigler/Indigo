#include "AABB.h"

using namespace Indigo;

AABB::AABB()
{
  min = glm::vec3(0);
  max = glm::vec3(0);
}

//Calculates from transformed vertices
void AABB::Recalc(std::vector<glm::vec3> &_verts)
{
  glm::vec3 tMin = _verts.at(0);
  glm::vec3 tMax = _verts.at(0);

  for (auto i = ++_verts.begin(); i != _verts.end(); i++)
  {
    tMin = glm::min(tMin, (*i));
    tMax = glm::max(tMax, (*i));
  }
  min = tMin;
  max = tMax;
}

void AABB::UpdateFromPrev(glm::mat4 _modelMat)
{
  //Transforms current bounding volume using _modelMat
  //creates new estimated bounding volume from this
  glm::vec3 rotatedMin = glm::vec3(_modelMat * glm::vec4(min, 1.0f));
  glm::vec3 rotatedMax = glm::vec3(_modelMat * glm::vec4(max, 1.0f));

  if (glm::min(rotatedMin, rotatedMax) == rotatedMin)
  {
    min = rotatedMin;
    max = rotatedMax;
  }
  else //Min value changed due to the transformation
  {
    min = rotatedMax;
    max = rotatedMin;
  }

}


//Dereferences this and calls static
bool AABB::Test(AABB _against)
{
  return AABB::Test(*this, _against);
}
bool AABB::Test(AABB _a, AABB _b)
{
  //Re-ordered to use x and z test first
  if (_a.max.z < _b.min.z || _a.min.z > _b.max.z) return false;
  if (_a.max.x < _b.min.x || _a.min.x > _b.max.x) return false;
  if (_a.max.y < _b.min.y || _a.min.y > _b.max.y) return false;

  return true;
}