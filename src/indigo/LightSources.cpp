#include "LightSources.h"

#include "GameObject.h"
#include "Transform.h"

#include "Light.h"
#include "Shader.h"

using namespace Indigo;

std::vector< std::weak_ptr<Light> > LightSources::allLights;

void LightSources::BufferLights(std::shared_ptr<Shader> _to, std::string _uniformArrName)
{
  std::string uniformOpenName = _uniformArrName + '[';

  int pointLights = 0;

  int lightNum = 0;
  for (auto l = allLights.begin(); l != allLights.end(); l++)
  {
    //Removing non-existant light references
    if (l->expired())
    {
      allLights.erase(l);
      l--;
      //continue; ?
    }

    switch (l->lock()->type)
    {
      case LightType::point:
      {
        std::string uniformFull = uniformOpenName + std::to_string(pointLights) + ']';
        _to->SetVec4(std::string(uniformFull + ".pos"), glm::vec4(l->lock()->transform->GetPosition(), 1.0f));
        _to->SetVec3(std::string(uniformFull + ".colour"), l->lock()->GetColour());
        _to->SetFloat(std::string(uniformFull + ".attenuation"), l->lock()->GetAttenuatation());
        pointLights++;
        break;
      }
      case LightType::directional:
      {
        break;
      }
    }
    lightNum++;
    if (lightNum > 15) break;
  }

  _to->SetInt("numPointLights", pointLights);
  
}

void LightSources::RegisterLight(std::weak_ptr<Light> _l)
{
  allLights.push_back(_l);
}