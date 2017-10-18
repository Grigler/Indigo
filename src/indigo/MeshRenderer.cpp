#include "MeshRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "Resources.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

using namespace Indigo;

MeshRenderer::MeshRenderer()
{
  mesh = std::make_unique<Mesh>();
}

void MeshRenderer::Update()
{
  if (parent.lock()->transform->_CheckForAABBRecalc())
  {
    glm::mat4 modelMat = parent.lock()->transform->GetModelMat();
  }
}
void MeshRenderer::Draw()
{
  //Activate the Mesh's VAO
  mesh->ActivateVAO();
  shader->Activate();

  {
    //Uniforms and such here
    std::weak_ptr<Camera> cam = Camera::currentActive;
    glm::mat4 identity = cam.lock()->GetIdentity();
    //TODO - other stuff

    glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertCount());
  }

  glBindVertexArray(0);

}

void MeshRenderer::LoadMesh(std::string _path)
{
  mesh->Assign(Resources::LoadMesh(_path));
}