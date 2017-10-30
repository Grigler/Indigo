#ifndef __IND_AABB__
#define __IND_AABB__

#include <vector>

#include <glm/glm.hpp>

namespace Indigo
{
  class AABB
  {
    friend class Camera;
  public:
    AABB();
    //Recalculates from 
    void Recalc(std::vector<glm::vec3> &_verts);
    //Uses current values and given modelMatrix to
    //create a new estimated AABB
    void UpdateFromPrev(glm::mat4 _modelMat);

    //Dereferences this and calls static test
    static bool Test(AABB _a, AABB _b);

  private:
    glm::vec3 min;
    glm::vec3 max;

  };
}

#endif