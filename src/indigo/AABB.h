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
    //update pre-existing AABB
    void Update(glm::mat4 _modelMat);

    //Dereferences this and calls static test
    static bool Test(AABB _a, AABB _b);

  private:
    glm::vec3 min;
    glm::vec3 max;

    glm::vec3 origMin;
    glm::vec3 origMax;

  };
}

#endif