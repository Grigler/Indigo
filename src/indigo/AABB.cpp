#include "AABB.h"

#include <glm/gtx/transform.hpp>

using namespace Indigo;

AABB::AABB()
{
  min = glm::vec3(0);
  max = glm::vec3(0);
}

//Calculates from transformed vertices
void AABB::Recalc(std::vector<glm::vec3> &_verts)
{
  //No verts to build an AABB from
  if (_verts.size() == 0) return;

  glm::vec3 tMin = glm::vec3(0), tMax = glm::vec3(0);

  tMin = _verts.at(0);
  tMax = _verts.at(0);


  for (auto i = ++_verts.begin(); i != _verts.end(); i++)
  {
    tMin = glm::min(tMin, (*i));
    tMax = glm::max(tMax, (*i));
  }
  min = tMin;
  max = tMax;
  origMin = min;
  origMax = max;
}

void AABB::Update(glm::mat4 _modelMat)
{
  /*
  *  Adapted from "Real Time Collision Detection" by Christer Ericson, 2005
  *  ISBN: 1-55860-732-3
  *  Chapter 4.2.6 - Page 86
  */
  //Transformation from _modelMat
  glm::vec3 t = _modelMat[3];
  //Moving rotation and scale parts into a mat3
  glm::mat3 rot = _modelMat;
  
  glm::vec3 nMin, nMax;

  for (int i = 0; i < 3; i++)
  {
    //Accounting for transformation
    nMin[i] = nMax[i] = t[i];
    for (int j = 0; j < 3; j++)
    {
      //Rotating on relevant axis
      float e = rot[i][j] * origMin[j];
      float f = rot[i][j] * origMax[j];
      //Adding to min or max depending on size
      if (e < f)
      {
        nMin[i] += e;
        nMax[i] += f;
      }
      else
      {
        nMin[i] += f;
        nMax[i] += e;
      }
    }
  }

  //Re-assigning to new values
  min = nMin;
  max = nMax;
}

bool AABB::Test(AABB _a, AABB _b)
{
  //Re-ordered to use x and z test first
  if (_a.max.z < _b.min.z || _a.min.z > _b.max.z) return false;
  if (_a.max.x < _b.min.x || _a.min.x > _b.max.x) return false;
  if (_a.max.y < _b.min.y || _a.min.y > _b.max.y) return false;

  return true;
}
bool AABB::Test(std::weak_ptr<AABB> _a, std::weak_ptr<AABB> _b)
{
  AABB a = *_a.lock().get();
  AABB b = *_b.lock().get();

  //Re-ordered to use x and z test first
  if (a.max.z < b.min.z || a.min.z > b.max.z) return false;
  if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
  if (a.max.y < b.min.y || a.min.y > b.max.y) return false;

  return true;
}
bool AABB::Against(AABB _b)
{
  //Re-ordered to use x and z test first
  if (max.z < _b.min.z || min.z > _b.max.z) return false;
  if (max.x < _b.min.x || min.x > _b.max.x) return false;
  if (max.y < _b.min.y || min.y > _b.max.y) return false;

  return true;
}