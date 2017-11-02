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

//DEBUG
#include <iostream>

using namespace Indigo;

std::weak_ptr<Camera> Camera::currentActive;

void Camera::onCreation()
{
  fov = 90.0f;

  CalcFrustumBV();
}

void Camera::onLateUpdate()
{
  if (parent.lock()->transform->_CheckForAABBRecalc())
  {
    frustumBV.Update(parent.lock()->transform->GetModelMat());
    parent.lock()->transform->_aabbNeedRecalc = false;
  }
}

void Camera::CalcFrustumBV()
{
  /* Calculating AABB to encompass camera frustum
  *
  *  This uses the far plane's dimensions for the xzy sizes
  *  although it would be more effective at culling nearby complex geometry
  *  (assuming an LOD system is used) to use a collection of AABBs using
  *  varying sizes down the frustum, a single one has been used for simplicity
  */
  float heightFar = 2.0f * glm::tan(fov / 2) * -1000.0f;
  float widthFar = heightFar * (1280.0f / 720.0f);

  std::shared_ptr<Transform> trans = parent.lock()->transform;
  glm::vec3 farCenter = trans->GetPosition() + trans->GetForward() * -1000.0f;
  glm::vec3 ftr = glm::vec3(farCenter.x, farCenter.y, -1000.0f) + (trans->GetUp() * heightFar / 2.0f) +
    (trans->GetRight() * widthFar / 2.0f);

  frustumBV.max = ftr;
  frustumBV.origMax = frustumBV.max;

  //float heightNear = 2.0f * glm::tan(fov / 2) * 0.3f;
  //float widthNear = heightNear * (1280.0f / 720.0f);

  glm::vec3 nearCenter = trans->GetPosition() + trans->GetForward() * -0.3f;
  glm::vec3 fbr = farCenter + (trans->GetRight()*widthFar / 2.0f) - (trans->GetUp()*heightFar / 2.0f);

  frustumBV.min = glm::vec3((ftr - trans->GetRight()*widthFar).x, fbr.y, nearCenter.z);
  frustumBV.origMin = frustumBV.min;

  printf("Min: %f %f %f\n", frustumBV.min.x, frustumBV.min.y, frustumBV.min.z);
  printf("Max: %f %f %f\n\n", frustumBV.max.x, frustumBV.max.y, frustumBV.max.z);

  parent.lock()->transform->_aabbNeedRecalc = false;
}

void Camera::Render()
{
  //Horrible hack to get around having to use shared_from_this
  //currentActive = parent.lock()->GetComponent<Camera>();
  //Converting to list due to constant removals
  std::list<std::shared_ptr<GameObject>> allObjsCopy;
  std::copy(Application::engineContext->gameObjects.begin(), Application::engineContext->gameObjects.end(),
    std::back_inserter(allObjsCopy));

  allObjsCopy.sort(LeftCloser); //List version

  //Draw calls
  for (auto i = allObjsCopy.begin(); i != allObjsCopy.end(); i++)
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
  }
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