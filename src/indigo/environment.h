#ifndef __IND_ENVIRONMENT__
#define __IND_ENVIRONMENT__

//Include for smart pointers
#include <memory>
#include <string>

namespace Indigo
{

  class Scene;
  class KeyHandler;

  class Environment
  {
  public:
    
    static void Environment::StartUp();

    //Static Time value getters
    //Returns delta from last frame in Seconds
    static float GetDT() { return instance->dtS; }
    //Returns Total time since game launch in Seconds
    static float GetRunTime() { return instance->runTime; }
    //Return raw pointer to scene graph
    static Scene *GetSceneGraph() { return instance->sceneGraph.get(); }

    static void Run();

  private:
    
    //Singleton to allow for simple static variable access
    //Like Environment::GetDT(); or Environment::GetRunTime();
    static Environment* instance;

    KeyHandler *keyHandler;

    //Creates generic empty scene
    Environment();
    //Loads "Scene/level" from file
    Environment(std::string _sceneFile);

    //Accessability values that also allow for simple access across all other 
    float dtS;
    float runTime;

    float minFixedDtS;

    std::shared_ptr<Scene> sceneGraph;

    //Used as the idle for glutMainLoop
    static void Update();

  };

} //End of namespace

#endif