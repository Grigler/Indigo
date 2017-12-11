#include "MeshRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "Resources.h"
#include "Mesh.h"

#include "Texture.h"
#include "TextureResource.h"

#include "Shader.h"
#include "Camera.h"

#include "LightSources.h"

#include <glm/gtx/transform.hpp>

using namespace Indigo;

MeshRenderer::MeshRenderer()
{
  mesh = std::make_shared<Mesh>();
  mesh->goParent = parent;

  texture = std::make_shared<Texture>();
  texture->goParent = parent;

  shader = Resources::GetShaderProgram("Basic");
  if (shader.expired())
  {
    printf("\tLoaded Fresh\n");
    shader = Shader::CreateShaderResource();
    shader.lock()->Init("Basic");
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
  mesh->ActivateVAO();
  shader.lock()->Activate();

  {
    std::weak_ptr<Camera> cam = Camera::currentActive;
    glm::mat4 model = parent->transform->GetModelMat();
    glm::mat4 vp = cam.lock()->GetViewProj();
    
    glm::mat4 mvp = vp*model;

    shader.lock()->SetMat4("MVP", mvp);
    shader.lock()->SetMat4("modelMat", model);
    shader.lock()->SetVec3("eyePos", cam.lock()->transform->GetPosition());
    
    LightSources::BufferLights(shader.lock(), "pointLights");

    if (texture.get() != nullptr)
    {
      glActiveTexture(GL_TEXTURE0);
      texture->Bind();
    }

    glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertCount());

    glBindTexture(GL_TEXTURE_2D, 0);
  }
}

void MeshRenderer::LoadMesh(std::string _path)
{
  mesh->Assign(Resources::LoadMesh(_path));
}
void MeshRenderer::LoadTexture(std::string _path)
{
  texture->Assign(Resources::LoadTexture(_path));
}