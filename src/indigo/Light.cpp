#include "Light.h"

#include "GameObject.h"

#include "LightSources.h"

using namespace Indigo;



void Light::onCreation()
{
  //Initialised to white
  colour = glm::vec3(1.0f);
  type = LightType::point;
  attenuation = 5.0f;

  //Registering Light
  LightSources::RegisterLight(parent->GetComponent<Light>());
}