#include "Environment.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "Scene.h"
#include "RenderManager.h"

using namespace Indigo;

Environment* Environment::instance = nullptr;

void Environment::StartUp()
{
  if (instance != nullptr)
  {
    throw std::exception();
    return;
  }
  instance = new Environment;
}

void Environment::StartUp(std::string _sceneFile)
{
  if (instance != nullptr)
  {
    throw std::exception();
    return;
  }
  instance = new Environment(_sceneFile);
}

Environment::Environment()
{
  //Equivalent to "unsafePtr = new Scene();"
  
  sceneGraph = std::make_shared<Scene>();
}

Environment::Environment(std::string _sceneFile)
{
  //TODO - Would be replaced with a string for filepath
  sceneGraph = std::make_shared<Scene>();
}

void Environment::Update()
{
  //TODO - update delta time and fixedTime stuff here

  instance->sceneGraph->tick();

  RenderManager::instance->Draw();

  //Would simply need to iterate over multiple scenes if that route
  //is taken in the future
}