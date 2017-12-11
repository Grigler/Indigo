#include "Mesh.h"

#include "MeshResource.h"

#include "AABB.h"

#include <glm/mat4x4.hpp>
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
  aabb->Update(_modelMat);
}