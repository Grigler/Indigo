#include "MeshRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "Resources.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

#include "meshShader.h"

#include <glm/gtx/transform.hpp>

using namespace Indigo;

MeshRenderer::MeshRenderer()
{
  mesh = std::make_shared<Mesh>();

  shader = std::make_shared<MeshShader>();
  shader->Init();
  std::dynamic_pointer_cast<MeshShader>(shader)->LoadDefaultShaders();
  shader->Link();

}

void MeshRenderer::onUpdate()
{
  if (parent.lock()->transform->_CheckForAABBRecalc())
  {
    glm::mat4 modelMat = parent.lock()->transform->GetModelMat();
    mesh->_updateAABB(modelMat);
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
    //TODO - other stuff
    glm::mat4 model = parent.lock()->transform->GetModelMat();
    glm::mat4 vp = cam.lock()->GetViewProj();
    
    glm::mat4 mvp = vp*model;

    glUniformMatrix4fv(std::dynamic_pointer_cast<MeshShader>(shader)->mvpHandle,
      1, GL_FALSE, &mvp[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertCount());
  }

  //glBindVertexArray(0);
}

void MeshRenderer::LoadMesh(std::string _path)
{
  mesh->Assign(Resources::LoadMesh(_path));
}