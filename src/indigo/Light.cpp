#include "Light.h"

#include "GameObject.h"

#include "LightSources.h"

using namespace Indigo;



void Light::onCreation()
{
  //Initialised to white
  colour = glm::vec3(1.0f);
  type = LightType::point;

  //Registering Light
  LightSources::RegisterLight(parent.lock()->GetComponent<Light>());
}