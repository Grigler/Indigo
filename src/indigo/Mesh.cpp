#include "Mesh.h"

#include "MeshResource.h"

#include "AABB.h"

#include <glm/gtx/transform.hpp>
#include <vector>

using namespace Indigo;

Mesh::Mesh()
{
  aabb = std::make_shared<AABB>();
}

void Mesh::Assign(std::weak_ptr<MeshResource> _m)
{
  meshResource = _m.lock();
  aabb->Recalc(*(meshResource->GetVerts()));
}
void Mesh::ActivateVAO()
{
  meshResource->ActivateVAO();
}

GLsizei Mesh::GetVertCount()
{
  return meshResource->GetVertCount();
}


void Mesh::_updateAABB(glm::mat4 _modelMat)
{
  /*
  std::vector<glm::vec3> modelVerts = *(meshResource->GetVerts());

  //Parallelising this using opm actually slowed it down, possibly
  //from caches misses or something
  for (int i = 0; i < modelVerts.size(); i++)
  {
    modelVerts.at(i) = _modelMat * glm::vec4(modelVerts.at(i), 1.0f);
  }
  */

  aabb->Update(_modelMat);
}