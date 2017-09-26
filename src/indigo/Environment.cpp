#include "Environment.h"

#include "Scene.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

using namespace Indigo;

Environment::Environment()
{
  //Equivalent to "unsafePtr = new Scene();"
  sceneGraph = std::make_shared<Scene>();
}

Environment::Environment(std::string _sceneFile)
{
  //Would be replaced with a string for filepath
  sceneGraph = std::make_shared<Scene>();
}

void Environment::Update()
{
  //TODO - update delta time and fixedTime stuff here

  sceneGraph->tick(dtS);

  //Would simply need to iterate over multiple scenes if that route
  //is taken in the future
}