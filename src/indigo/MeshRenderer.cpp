#include "MeshRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "Resources.h"
#include "Mesh.h"

using namespace Indigo;

void MeshRenderer::Update()
{
  if (parent.lock()->transform->_CheckForAABBRecalc())
  {
    glm::mat4 modelMat = parent.lock()->transform->GetModelMat();
  }
}

void MeshRenderer::LoadMesh(std::string _path)
{
  mesh.lock()->Assign(Resources::LoadMesh(_path));
}