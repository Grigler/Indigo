#ifndef __IND_AABB__
#define __IND_AABB__

#include <vector>

#include <glm/glm.hpp>

namespace Indigo
{
  class AABB
  {
  public:
    
    inline void Recalc(std::vector<glm::vec3> _verts);
    //Dereferences this and calls static test
    inline bool Test(AABB _against);
    //Generic public static for testing collision
    //between two AABBs
    inline static bool Test(AABB _a, AABB _b);

    void SetPos(glm::vec3 _p) { centerPos = _p; }
    //Scales offset xyz by _s xyz
    void SetScale(glm::vec3 _s);
    void TransPos(glm::vec3 _deltaP) { centerPos += _deltaP; }

  private:
    //Using centerPoint and offset
    //in xyz for sizes
    glm::vec3 centerPos;
    glm::vec3 offset;

  };
}

#endif