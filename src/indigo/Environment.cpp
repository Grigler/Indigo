#include "Environment.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "Scene.h"

#include "RenderManager.h"
#include "KeyHandler.h"

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

  instance->keyHandler = new KeyHandler();
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

void Environment::Run()
{
  glutIdleFunc(Update);
  glutMainLoop();
}

void Environment::Update()
{
  //TODO - update delta time and fixedTime

  //Sending tick down heirarchal scene graph
  instance->sceneGraph->tick();
  //Calling render manager to draw the scene
  glutPostRedisplay();
}