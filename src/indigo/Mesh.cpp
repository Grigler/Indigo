#include "Mesh.h"

#include "MeshResource.h"

#include <glm/gtx/transform.hpp>
#include <vector>

using namespace Indigo;

void Mesh::_updateAABB(glm::mat4 _modelMat)
{
  std::vector<glm::vec3> modelVerts = *(meshResource->GetVerts());

  //TODO - TEST THIS ACTUALLY WORKS HERE
#pragma omp parallel for
  for (int i = 0; i < modelVerts.size(); i++)
  {
    modelVerts.at(i) = _modelMat * glm::vec4(modelVerts.at(i), 1.0f);
  }
  
  aabb.Recalc(modelVerts);
}