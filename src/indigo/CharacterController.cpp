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
  mouseSens = glm::vec2(1.0f);
}

void CharacterController::onUpdate()
{
  UpdateRotFromMouse();

  UpdatePosFromKeys();
}

void CharacterController::UpdateRotFromMouse()
{
  std::weak_ptr<Transform> t = parent.lock()->transform;

  glm::vec2 mouseDelta = Input::GetMouseDeltaRaw();
  //printf("MouseDelta: %f, %f\n", mouseDelta.x, mouseDelta.y);

  glm::vec3 r = transform.lock()->GetRotation();
  //printf("R before: %f, %f, %f\n", r.x, r.y, r.z);

  r.y -= mouseSens.x * mouseDelta.x * Application::GetDT();
  r.x += mouseSens.y * mouseDelta.y * Application::GetDT();

  //Clamping to stop camera tumbling
  if (r.x > glm::radians(180.0f))
    r.x = glm::radians(180.0f);
  if (r.x < glm::radians(-180.0f))
    r.x = glm::radians(-180.0f);

  //printf("R after: %f, %f, %f\n\n", r.x, r.y, r.z);

  transform.lock()->SetRotation(r);

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
    moveVec += t.lock()->GetRight() * moveSpeed;
  }
  if (Input::GetKey('q') || Input::GetKey('Q'))
  {
    moveVec += t.lock()->GetRight() * -moveSpeed;
  }

  t.lock()->SetPosition(t.lock()->GetPosition() + moveVec * Application::GetDT());

  //t.lock()->Translate(moveVec * Application::GetDT());
  //t.lock()->MoveDir(moveVec, moveSpeed*Application::GetDT());
}