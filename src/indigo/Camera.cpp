#include "Camera.h"

#include "glm/glm.hpp"

#include "Application.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"

#include <vector>
#include <list>
#include <iterator>
#include <memory>
#include <algorithm>

using namespace Indigo;

std::weak_ptr<Camera> Camera::currentActive;

void Camera::Render()
{
  //Horrible hack to get around having to use shared_from_this
  //currentActive = parent.lock()->GetComponent<Camera>();
  //Converting to list due to constant removals
  std::list<std::shared_ptr<GameObject>> allObjsCopy;
  std::copy(Application::engineContext->gameObjects.begin(), Application::engineContext->gameObjects.end(),
    std::back_inserter(allObjsCopy));
 /* 
  glm::vec3 forward = parent.lock()->transform->GetForward();
  glm::vec3 pos = parent.lock()->transform->GetPosition();

  //Removing all objects behind the camera
  for (auto i = allObjsCopy.begin(); i != allObjsCopy.end(); i++)
  {
    glm::vec3 dir = (*i)->transform->GetPosition() - pos;
    if (glm::dot(forward, dir) <= 0.0f)
    {
      allObjsCopy.erase(i);
    }
  }
  */
  //Sort by distance to camera
  //std::sort(allObjsCopy.begin(), allObjsCopy.end(), LeftCloser);
  allObjsCopy.sort(LeftCloser); //List version
  //Frustum culling here

  //Draw calls
  for (auto i = allObjsCopy.begin(); i != allObjsCopy.end(); i++)
  {
	  (*i)->Draw();
  }

  //currentActive.reset();
}

void Camera::MakeActive()
{
  currentActive = parent.lock()->GetComponent<Camera>();
}

bool Camera::LeftCloser(std::shared_ptr<GameObject> l, std::shared_ptr<GameObject> r)
{
  return (glm::distance(l->transform->GetPosition(),
    currentActive.lock()->parent.lock()->transform->GetPosition())
    <
    glm::distance(r->transform->GetPosition(),
      currentActive.lock()->parent.lock()->transform->GetPosition()));
}