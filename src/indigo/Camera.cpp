#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Application.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Mesh.h"

#include <vector>
#include <list>
#include <iterator>
#include <memory>
#include <algorithm>

using namespace Indigo;

std::weak_ptr<Camera> Camera::currentActive;

void Camera::onCreation()
{
  fov = 90.0f;
  //Calculating needed frustum vertex points in world space
  glm::mat4 inverseVP = glm::inverse(GetViewProj());

  float heightFar = 2.0f * glm::tan(fov / 2) * 1000.0f;
  float widthFar = heightFar * (1280.0f / 720.0f);

  std::shared_ptr<Transform> trans = parent.lock()->transform;
  glm::vec3 farCenter = trans->GetPosition() + trans->GetForward() * -1000.0f;
  glm::vec3 ftr = farCenter + (trans->GetUp() * heightFar / 2.0f) +
    (trans->GetRight() * widthFar / 2.0f);

  frustumBV.max = ftr;

  float heightNear = 2.0f * glm::tan(fov / 2) * 0.3f;
  float widthNear = heightNear * (1280.0f / 720.0f);

  glm::vec3 nearCenter = trans->GetPosition() + trans->GetForward() * 0.3f;
  //glm::vec3 nbr = nearCenter - (trans->GetUp() * heightNear / 2.0f) + (trans->GetRight()*widthNear / 2.0f);
  glm::vec3 fbr = farCenter + (trans->GetRight()*widthFar / 2.0f) - (trans->GetUp()*heightFar / 2.0f);

  frustumBV.min = glm::vec3((ftr - trans->GetRight()*widthFar).x , fbr.y, -nearCenter.z);

  //Forming a min-max AABB BV for the frustum
  //frustumBV.min = glm::vec3(fbr.x, minY, nbr.z);
  //frustumBV.max = ftl;

}

void Camera::Render()
{
  //Horrible hack to get around having to use shared_from_this
  //currentActive = parent.lock()->GetComponent<Camera>();
  //Converting to list due to constant removals
  std::list<std::shared_ptr<GameObject>> allObjsCopy;
  std::copy(Application::engineContext->gameObjects.begin(), Application::engineContext->gameObjects.end(),
    std::back_inserter(allObjsCopy));
  
  glm::vec3 forward = parent.lock()->transform->GetForward();
  glm::vec3 pos = parent.lock()->transform->GetPosition();

  allObjsCopy.sort(LeftCloser); //List version

  //Draw calls
  for (auto i = allObjsCopy.begin(); i != allObjsCopy.end(); i++)
  {
    glm::vec3 dir = (*i)->transform->GetPosition() - pos;
    if (glm::dot(forward, dir) <= 0.0f)
    {
      //std::weak_ptr<RenderComponent> rc = (*i)->GetRenderComponent();
      //TODO - change to switch on some enum or string in base then cast
      //std::weak_ptr<MeshRenderer> mr = std::dynamic_pointer_cast<MeshRenderer>(rc.lock());
      std::weak_ptr<MeshRenderer> mr = (*i)->GetComponent<MeshRenderer>();
      if (mr.expired()) continue;
      if (AABB::Test(frustumBV, mr.lock()->mesh->aabb))
      {
        (*i)->Draw();
      }
      else
      {
        //printf("Fail\n");
      }
    }
  }

  //currentActive.reset();
}

void Camera::MakeActive()
{
  currentActive = parent.lock()->GetComponent<Camera>();
}

glm::mat4 Camera::GetViewProj()
{
  glm::mat4 view = glm::inverse(parent.lock()->transform->GetModelMat());
  //TODO - Change to have better customisability
  glm::mat4 proj = glm::perspective(fov, 1280.0f / 720.0f, 0.3f, 1000.0f);
  return proj * view;
}

bool Camera::LeftCloser(std::shared_ptr<GameObject> l, std::shared_ptr<GameObject> r)
{
  return (glm::distance(l->transform->GetPosition(),
    currentActive.lock()->parent.lock()->transform->GetPosition())
    <
    glm::distance(r->transform->GetPosition(),
      currentActive.lock()->parent.lock()->transform->GetPosition()));
}