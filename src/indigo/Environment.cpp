#include "environment.h"

#include "Scene.h"

using namespace Indigo;

Environment::Environment()
{
  //Equivalent to "unsafePtr = new Scene();"
  scene = std::make_shared<Scene>();
}

Environment::Environment(std::string _sceneFile)
{
  //Would be replaced with a string for filepath
  scene = std::make_shared<Scene>();
}


void Environment::Update()
{

}