#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Application.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "RenderBuffer.h"
#include "Shader.h"

#include <vector>
#include <list>
#include <iterator>
#include <memory>
#include <algorithm>

//DEBUG
#include <iostream>
#include "Input.h"

using namespace Indigo;

std::weak_ptr<Camera> Camera::currentActive;
std::shared_ptr<RenderBuffer> Camera::rb;

void Camera::onCreation()
{
  
  fov = glm::radians(90.0f);
  near = 0.01f;
  far = 1000.0f;

  //Partitions the frustum into 32 AABB segments
  //used for frustum culling
  CalcFrustumBVPartitions(32);

  if (rb.get() == NULL)
  {
	  rb = std::make_shared<RenderBuffer>();
	  rb->GenBuffers(1280, 720);

	  std::shared_ptr<Shader> postProcess = std::make_shared<Shader>();
	  postProcess->Init("postProcess");
	  postProcess->LoadShader(GL_VERTEX_SHADER, "./data/Shaders/Post-Process/Quad.vert");
	  postProcess->LoadShader(GL_FRAGMENT_SHADER, "./data/Shaders/Post-Process/Quad.frag");
	  postProcess->Link();

	  rb->AttachShader(postProcess);
  }
}

void Camera::onLateUpdate()
{
  if (parent.lock()->transform->_CheckForAABBRecalc())
  {
    //frustumBV.Update(parent.lock()->transform->GetModelMat());
    for (auto i = frustumBVs.begin(); i != frustumBVs.end(); i++)
    {
      i->Update(transform.lock()->GetModelMat());
    }
    parent.lock()->transform->_aabbNeedRecalc = false;
  }
}

void Camera::CalcFrustumBVPartitions(int _bvNum)
{
  //Clearing it if frustumBVs need to be re-calculated at run-time
  frustumBVs.clear();

  std::shared_ptr<Transform> t = transform.lock();

  glm::vec3 posForward = t->GetPosition() + t->GetForward();

  float dist = far - near;
  float segSize = dist / _bvNum;

  for (int i = 0; i < _bvNum; i++)
  {
    float distFar = (dist - (segSize*i));
    float distNear = distFar - segSize;

    float hFar = 2.0f * glm::tan(fov / 2.0f) * distFar;
    float wFar = hFar * (1280.0f / 720.0f);

    glm::vec3 farCent = posForward + distFar;
    glm::vec3 nearCent = posForward + distNear;

    //Top-Right of far plane
    glm::vec3 max = farCent + (t->GetRight()*wFar*0.5f) + (t->GetUp()*hFar*0.5f);
    //Bottom-right of far plane with width and height of far plane
    glm::vec3 min = nearCent - (t->GetRight()*wFar*0.5f) - (t->GetUp()*hFar*0.5f);

    AABB bv;
    bv.min = min;
    bv.max = max;
    bv.origMin = min;
    bv.origMax = max;
    frustumBVs.push_back(bv);
  }
}
bool Camera::InFrustum(std::weak_ptr<AABB> _bv)
{
  AABB bv = *_bv.lock().get();
  for (auto i = frustumBVs.begin(); i != frustumBVs.end(); i++)
  {
    if (i->Against(bv))
    {
      return true;
    }
  }
  return false;
}

void Camera::Render()
{
  std::list<std::shared_ptr<GameObject>> allObjsCopy;
  std::copy(Application::engineContext->gameObjects.begin(), Application::engineContext->gameObjects.end(),
    std::back_inserter(allObjsCopy));

  //Sorting the objects by distance to the camera so that closer objects are drawn first
  //this means that there should be less uneccessary fragment operations that will
  //later fail depth testing
  allObjsCopy.sort(LeftCloser);

  //Get and assign the framebuffer
  rb->Bind();

  //Draw calls
  for (auto i = allObjsCopy.begin(); i != allObjsCopy.end(); i++)
  {
    std::weak_ptr<MeshRenderer> mr = (*i)->GetComponent<MeshRenderer>();
    if (mr.expired()) continue;

    //Testing objects against the viewing frustum BV and then drawing if they pass
    //this allows for simplistic frustum-culling
    if (InFrustum(mr.lock()->mesh->aabb))
    {
      (*i)->Draw();
    }
  }

  //Post processing effects here (hdr - gamma correction)
  rb->DrawToQuad(1280, 720);
}

void Camera::MakeActive()
{
  currentActive = parent.lock()->GetComponent<Camera>();
}

glm::mat4 Camera::GetViewProj()
{
  //glm::mat4 view = glm::inverse(parent.lock()->transform->GetModelMat());
  //glm::mat4 view = glm::lookAt(transform.lock()->GetPosition(),
  //  transform.lock()->GetPosition() + transform.lock()->GetForward(),
  // transform.lock()->GetUp());
  glm::mat4 view = glm::lookAtRH(transform.lock()->GetPosition(),
	  transform.lock()->GetPosition()+transform.lock()->GetForward(),
	  transform.lock()->GetUp());

  //TODO - Change to have better customisability
  glm::mat4 proj = glm::perspective(fov, 1280.0f / 720.0f, 0.01f, 1000.0f);
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