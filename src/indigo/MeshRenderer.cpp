#include "MeshRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "Resources.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

#include "meshShader.h"

#include "LightSources.h"

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
    //shader.lock()->LoadShader(GL_VERTEX_SHADER,
    //  "./data/Shaders/MeshRenderer/MeshRenderer.vert");
    //shader.lock()->LoadShader(GL_FRAGMENT_SHADER,
    //  "./data/Shaders/MeshRenderer/MeshRenderer.frag");

    shader.lock()->LoadShader(GL_VERTEX_SHADER,
      "./data/Shaders/Lighting/MeshLit.vert");
    shader.lock()->LoadShader(GL_FRAGMENT_SHADER,
      "./data/Shaders/Lighting/MeshLit.frag");

    shader.lock()->Link();
  }
}

void MeshRenderer::onUpdate()
{
  if (parent->transform->_CheckForAABBRecalc())
  {
    glm::mat4 modelMat = parent->transform->GetModelMat();
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
    glm::mat4 model = parent->transform->GetModelMat();
    glm::mat4 vp = cam.lock()->GetViewProj();
    
    glm::mat4 mvp = vp*model;

    //glUniformMatrix4fv(0,
    //  1, GL_FALSE, &mvp[0][0]);
    shader.lock()->SetMat4("MVP", mvp);
    shader.lock()->SetMat4("modelMat", model);
    shader.lock()->SetVec3("eyePos", cam.lock()->transform->GetPosition());
    
    LightSources::BufferLights(shader.lock(), "pointLights");


    glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertCount());
  }

  //glBindVertexArray(0);
}

void MeshRenderer::LoadMesh(std::string _path)
{
  mesh->Assign(Resources::LoadMesh(_path));
}