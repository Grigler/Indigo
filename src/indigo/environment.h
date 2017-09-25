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

    //Singleton to allow for simple static variable access
    //Like Environment::GetDT(); or Environment::GetRunTime();
    static std::unique_ptr<Environment> instance;

    //Static Time value getters
    //Returns delta from last frame in Seconds
    static float GetDT() { return instance->dtS; }
    //Returns Total time since game launch in Seconds
    static float GetRunTime() { return instance->runTime; }

    std::shared_ptr<Scene> sceneGraph;
    //Calls Tick() sceneGraph - will be easy to allow for multiple
    //concurrent scenes using this method
    void Update();

  private:
    
    //Accessability values that also allow for simple access across all other 
    float dtS;
    float runTime;

    float minFixedDtS;

  };

} //End of namespace

#endif