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

  glm::vec2 mouseDelta = Input::GetMouseDelta() * 10.0f;

  printf("R:%i\n", rand() % 255);

  printf("D: %f %f\n", mouseDelta.x, mouseDelta.y);
  
  float angleRotY = glm::sign(mouseDelta.x) * glm::degrees(glm::angle(glm::vec2(0, 1),
    glm::normalize(glm::vec2(mouseDelta.x, 1)))) * Application::GetDT() * mouseSens.y;
  float angleRotX = glm::sign(mouseDelta.y) * glm::degrees(glm::angle(glm::vec2(0, 1),
    glm::normalize(glm::vec2(mouseDelta.y, 1)))) * Application::GetDT() * mouseSens.x;

  angleRotX /= 10.0f;
  angleRotY /= 10.0f;

  printf("Angles: %f %f\n", angleRotX, angleRotY);
  /*
  glm::mat4 rotationMat = glm::mat4(1);
  rotationMat = glm::rotate(rotationMat, angleRotY, glm::vec3(0, 1, 0));
  rotationMat = glm::rotate(rotationMat, angleRotX, glm::vec3(1, 0, 0));

  t.lock()->SetRotation(glm::vec4(t.lock()->GetRotation(),1)*rotationMat);
  */
  t.lock()->Rotate(glm::vec3(angleRotX, angleRotY, 0.0f));

  lastMouseDelta = mouseDelta;

  //Manually calling cam component update event
  //cam.onUpdate();
}