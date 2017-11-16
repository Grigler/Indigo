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
  mesh->goParent = parent;

  shader = Resources::GetShaderProgram("Basic");
  if (shader.expired())
  {
    printf("\tLoaded Fresh\n");
    shader = Shader::CreateShaderResource();
    shader.lock()->Init("Basic");
    //std::dynamic_pointer_cast<MeshShader>(shader.lock())->LoadDefaultShaders();
    shader.lock()->LoadShader(GL_VERTEX_SHADER,
      "C:/Users/i7465070/Indigo/data/Shaders/MeshRenderer/MeshRenderer.vert");
    shader.lock()->LoadShader(GL_FRAGMENT_SHADER,
      "C:/Users/i7465070/Indigo/data/Shaders/MeshRenderer/MeshRenderer.frag");
    shader.lock()->Link();
  }
  else
  {
    printf("\tLoaded from pool\n");
  }

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
  shader.lock()->Activate();

  {
    //Uniforms and such here
    std::weak_ptr<Camera> cam = Camera::currentActive;
    //TODO - other stuff
    glm::mat4 model = parent.lock()->transform->GetModelMat();
    glm::mat4 vp = cam.lock()->GetViewProj();
    
    glm::mat4 mvp = vp*model;

    glUniformMatrix4fv(0,
      1, GL_FALSE, &mvp[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertCount());
  }

  //glBindVertexArray(0);
}

void MeshRenderer::LoadMesh(std::string _path)
{
  mesh->Assign(Resources::LoadMesh(_path));
}