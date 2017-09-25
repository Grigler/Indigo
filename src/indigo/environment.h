#ifndef __IND_ENVIRONMENT__
#define __IND_ENVIRONMENT__

//Include for smart pointers
#include <memory>

namespace Indigo
{

  class Scene;

  class Environment
  {
  public:
    std::shared_ptr<Scene> scene;

    void Update();

  private:

  };

} //End of namespace

#endif