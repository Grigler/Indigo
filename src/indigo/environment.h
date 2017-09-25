#ifndef __IND_ENVIRONMENT__
#define __IND_ENVIRONMENT__

//Include for smart pointers
#include <memory>
#include <string>

namespace Indigo
{

  class Scene;

  class Environment
  {
  public:
    //Creates generic empty scene
    Environment();
    //Loads "Scene/level" from file
    Environment(std::string _sceneFile);

    std::shared_ptr<Scene> scene;

    void Update();

  private:

  };

} //End of namespace

#endif