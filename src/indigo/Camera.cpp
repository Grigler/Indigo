#include "Camera.h"

#include "glm/glm.hpp"

#include "Application.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"

#include <vector>
#include <memory>
#include <algorithm>

using namespace Indigo;

Camera *Camera::currentActive = nullptr;

void Camera::Render()
{
  currentActive = this;

  std::vector<std::shared_ptr<GameObject>> allObjsCopy
  (Application::engineContext->gameObjects);

  //Sort by distance to camera
  std::sort(allObjsCopy.begin(), allObjsCopy.end(), LeftCloser);
  //Frustum culling

  //Draw calls
  for (size_t i = 0; i < allObjsCopy.size(); i++)
  {
    allObjsCopy.at(i)->Draw();
  }

  currentActive = nullptr;
}

bool Camera::LeftCloser(std::shared_ptr<GameObject> l, std::shared_ptr<GameObject> r)
{
  return (glm::distance(l->transform->GetPosition(),
    currentActive->parent.lock()->transform->GetPosition())
    <
    glm::distance(r->transform->GetPosition(),
      currentActive->parent.lock()->transform->GetPosition()));
}