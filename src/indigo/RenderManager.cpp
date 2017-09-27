#include "RenderManager.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "Environment.h"
#include "Scene.h"
#include "GameObj.h"

//Held in register
#include "Camera.h"
#include "Window.h"

using namespace Indigo;

RenderManager *RenderManager::instance = nullptr;
//Constructors to create init glut and create context
RenderManager::RenderManager(int _argc, char *_argv[])
{
  //Generic warm-up of any back-end render systems
  //without any context creation
  glutInit(&_argc, _argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
}
RenderManager::RenderManager(int _argc, char *_argv[],
  unsigned int _winX, unsigned int _winY, bool _fullScreenFlag)
{
  //Generic warm-up of any back-end render systems
  //without any context creation
  glutInit(&_argc, _argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  //OpenGL context setting
  glutInitContextVersion(4, 5);
  glutInitContextFlags(GLUT_CORE_PROFILE); 
  //Creation of window context here
  glutInitWindowSize(_winX, _winY);
  glutCreateWindow("Initial Window");

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    throw std::exception();
  }
}

//Static StartUp functions to init singleton and call init system
void RenderManager::StartUp(int _argc, char *_argv[])
{
  if (instance != nullptr)
  {
    throw std::exception();
    return;
  }
  //Constructor will contain warm-up of any back-end render systems
  instance = new RenderManager(_argc, _argv);
}
void RenderManager::StartUp(int _argc, char *_argv[],
  unsigned int _winX, unsigned int _winY, bool _fullScreenFlag)
{
  if (instance != nullptr)
  {
    throw std::exception();
    return;
  }
  //Constructor will contain warm-up of any back-end render systems
  instance = new RenderManager(_argc, _argv, _winX, _winY, _fullScreenFlag);
}

void RenderManager::ShutDown()
{
  //TODO - Destroy render context
}

void RenderManager::Draw()
{
  std::list<GameObj*> allObjs = Environment::GetSceneGraph()->GetFullList();

  //TODO - batching, rather than a blanket draw-call over all game objects
  for (std::list<GameObj*>::iterator obj = allObjs.begin();
    obj != allObjs.end(); obj++)
  {
    (*obj)->onDraw();
  }

  glutSwapBuffers();
}

void RenderManager::RegisterCamera(Camera *_c)
{
  for (std::list<Camera*>::iterator i = instance->cameraRegister.begin();
    i != instance->cameraRegister.end(); i++)
  {
    if (_c == (*i))
    {
      return;
    }
  }

  instance->cameraRegister.push_back(_c);
}
void RenderManager::UnregisterCamera(Camera *_c)
{
  for (std::list<Camera*>::iterator i = instance->cameraRegister.begin();
    i != instance->cameraRegister.end(); i++)
  {
    if (_c == (*i))
    {
      instance->cameraRegister.erase(i);
      return;
    }
  }
}

void RenderManager::RegisterWindow(Window *_w)
{
  for (std::list<Window*>::iterator i = instance->windowRegister.begin();
    i != instance->windowRegister.end(); i++)
  {
    if (_w == (*i))
    {
      return;
    }
  }

  instance->windowRegister.push_back(_w);
}
void RenderManager::UnregisterWindow(Window *_w)
{
  for (std::list<Window*>::iterator i = instance->windowRegister.begin();
    i != instance->windowRegister.end(); i++)
  {
    if (_w == (*i))
    {
      instance->windowRegister.erase(i);
      return;
    }
  }
}
