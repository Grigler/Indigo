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
    
    static void Environment::StartUp();

    static void Environment::StartUp(std::string _sceneFile);

    //Static Time value getters
    //Returns delta from last frame in Seconds
    static float GetDT() { return instance->dtS; }
    //Returns Total time since game launch in Seconds
    static float GetRunTime() { return instance->runTime; }
    //Return raw pointer to scene graph
    static Scene *GetSceneGraph() { return instance->sceneGraph.get(); }
    
    //Calls Tick() sceneGraph - will be easy to allow for multiple
    //concurrent scenes using this method
    static void Update();

  private:
    
    //Singleton to allow for simple static variable access
    //Like Environment::GetDT(); or Environment::GetRunTime();
    static Environment* instance;

    //Creates generic empty scene
    Environment();
    //Loads "Scene/level" from file
    Environment(std::string _sceneFile);

    //Accessability values that also allow for simple access across all other 
    float dtS;
    float runTime;

    float minFixedDtS;

    std::shared_ptr<Scene> sceneGraph;

  };

} //End of namespace

#endif