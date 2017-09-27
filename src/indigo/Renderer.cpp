#include "Renderer.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "Camera.h"
#include "GameObj.h"
#include "Transform.h"

using namespace Indigo;

Camera *Renderer::currentCam = nullptr;

bool Renderer::closestFirst(GameObj *l, GameObj *r)
{
  return (glm::distance(l->trans->GetPosition(), currentCam->parentObj->trans->GetPosition())
    < glm::distance(r->trans->GetPosition(), currentCam->parentObj->trans->GetPosition()));
}
void Renderer::Render(Camera *_cam, std::list<GameObj*> _allObjs)
{
  currentCam = _cam;
  //TODO frustum culling first

  //Sorting remaining objects by distance to camera (closest first)
  _allObjs.sort(closestFirst);

  //Draw Calls
  
}