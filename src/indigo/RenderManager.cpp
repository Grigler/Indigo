#include "RenderManager.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

using namespace Indigo;

RenderManager *RenderManager::instance = nullptr;

RenderManager::RenderManager(int _argc, char *_argv[])
{
  //Generic warm-up of any back-end render systems
  //without any context creation
  glutInit(&_argc, _argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
}
RenderManager::RenderManager(int _argc, char *_argv[],
  glm::vec2 _winSize, bool _fullScreenFlag)
{
  //Generic warm-up of any back-end render systems
  //without any context creation
  glutInit(&_argc, _argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  //Creation of window context here
  glutInitWindowSize(_winSize.x, _winSize.y);
  glutCreateWindow("Initial Window");
  
}

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
  glm::vec2 _winSize, bool _fullScreenFlag)
{
  if (instance != nullptr)
  {
    throw std::exception();
    return;
  }
  //Constructor will contain warm-up of any back-end render systems
  instance = new RenderManager(_argc, _argv, _winSize, _fullScreenFlag);
}