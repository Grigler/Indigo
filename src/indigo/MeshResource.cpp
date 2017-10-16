#include "Mesh.h"

#include "MeshResource.h"

using namespace Indigo;

void Mesh::Assign(std::weak_ptr<MeshResource> _m)
{
  meshResource = _m.lock();
}