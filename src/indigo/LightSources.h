#ifndef __IND_LIGHT_SOURCES__
#define __IND_LIGHT_SOURCES__

#include <memory>
#include <vector>
#include <string>

namespace Indigo
{

  class Light;
  class Shader;

  class LightSources
  {
    friend class Light;
  public:

    //Sets uniform values for shader
    static void BufferLights(std::shared_ptr<Shader> _to, std::string _uniformArrName);

  private:
    static void RegisterLight(std::weak_ptr<Light> _l);

    static std::vector< std::weak_ptr<Light> > allLights;
  };

}

#endif