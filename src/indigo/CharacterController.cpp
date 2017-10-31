#include "CharacterController.h"

#include "Application.h"

#include "GameObject.h"
#include "Transform.h"

#include "Input.h"

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/transform.hpp>

using namespace Indigo;

void CharacterController::onCreation()
{


  //Manually calling cam component creation event
  //cam.onCreation();
}

void CharacterController::onUpdate()
{
  UpdateRotFromMouse();

  UpdatePosFromKeys();
}

void CharacterController::UpdateRotFromMouse()
{
  std::weak_ptr<Transform> t = parent.lock()->transform;

  glm::vec2 mouseDelta = Input::GetMouseDelta() * 10.0f;

  float angleRotY = glm::sign(mouseDelta.x) * glm::degrees(glm::angle(glm::vec2(0, 1),
    glm::normalize(glm::vec2(mouseDelta.x, 1)))) * Application::GetDT() * mouseSens.y;
  float angleRotX = glm::sign(mouseDelta.y) * glm::degrees(glm::angle(glm::vec2(0, 1),
    glm::normalize(glm::vec2(mouseDelta.y, 1)))) * Application::GetDT() * mouseSens.x;

  angleRotX /= 10.0f;
  angleRotY /= 10.0f;

  t.lock()->Rotate(glm::vec3(angleRotX, angleRotY, 0.0f));

  lastMouseDelta = mouseDelta;
}
void CharacterController::UpdatePosFromKeys()
{
  glm::vec3 moveVec = glm::vec3(0);
  std::weak_ptr<Transform> t = parent.lock()->transform;
  if (Input::GetKey('w') || Input::GetKey('W'))
  {
    moveVec += t.lock()->GetForward() * moveSpeed;
  }
  if (Input::GetKey('s') || Input::GetKey('S'))
  {
    moveVec += t.lock()->GetForward() * -moveSpeed;
  }

  if (Input::GetKey('e') || Input::GetKey('E'))
  {
    moveVec += t.lock()->GetRight() * -moveSpeed;
  }
  if (Input::GetKey('q') || Input::GetKey('Q'))
  {
    moveVec += t.lock()->GetRight() * moveSpeed;
  }

  t.lock()->SetPosition(t.lock()->GetPosition() + moveVec * Application::GetDT());
}