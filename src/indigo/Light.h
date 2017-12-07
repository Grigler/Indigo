#ifndef __IND_LIGHT__
#define __IND_LIGHT__

#include <glm/vec3.hpp>

#include "Component.h"

namespace Indigo
{
  
  enum LightType
  {
    point,
    directional
    //,spotlight
  };

  class Light : public Component
  {
  public:
    LightType type;

    void onCreation();

    //Uses normalized rgb values (0.0f-1.0f)
    glm::vec3 GetColour() { return colour; }
    void SetColour(glm::vec3 _rgb) { colour = _rgb; }

    float GetAttenuatation() { return attenuation; }
    void SetAttenuation(float _to) { attenuation = _to; }

  private:
    glm::vec3 colour;
    float attenuation;

  };

}

#endif