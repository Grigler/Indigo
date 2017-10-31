#include "Application.h"

#include "Engine.h"
#include "Input.h"

#include "GL/glew.h"
#include "GL/freeglut.h"

#include <iostream>

using namespace Indigo;

std::shared_ptr<Engine> Application::engineContext;
float Application::deltaTime = 0.0f;

void Application::Init(int _argc, char* _argv[])
{
  //Creating the engine context
  engineContext = std::make_shared<Engine>();

  //Init glut and create window context - also setup callbacks
  glutInit(&_argc, _argv);
  glutInitWindowSize(1280, 720);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitContextVersion(4, 5);
  glutInitContextFlags(GLUT_CORE_PROFILE);
  //TODO - replace with game-managed functionality
  glutCreateWindow("Indigo Testing");
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

  //Set up glut callbacks here
  glutIdleFunc(Idle);
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutKeyboardUpFunc(KeyboardUp);
  glutPassiveMotionFunc(MouseMotionPassive);
  glutMotionFunc(MouseMotionPassive);

  //Init glew
  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glClearColor(75.0f/255.0f, 0.0f, 130.0f/255.0f, 1.0f);
}
void Application::Kill()
{
  engineContext.reset();
}
void Application::ShutDown()
{
  RecenterMouse();
  glutLeaveMainLoop();
}
void Application::Run()
{
  try
  {
    glutMainLoop();
  }
  catch (std::exception e)
  {
    ErrPrint(e);
  }
}

float Application::GetDT()
{
  return deltaTime;
}

void Application::Idle()
{
  //Timer updating
  static float lastT = glutGet(GLUT_ELAPSED_TIME); //only run 1st time
  float t = glutGet(GLUT_ELAPSED_TIME);
  deltaTime = (t - lastT) / 1000.0f;
  lastT = glutGet(GLUT_ELAPSED_TIME);
  //Sleep for vSync here

  //Update all objects
  engineContext->Update();

  //DEBUG - QUITING ON ESCAPE KEY
  if (Input::GetKeyDown(27)) ShutDown();

  //Clearing upKeys buffer for next input polling
  Input::upKeys.clear();
  Input::downKeys.clear();

  glutPostRedisplay();
}
void Application::Display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  engineContext->Draw();
  glutSwapBuffers();
}
void Application::Keyboard(unsigned char _k, int _x, int _y)
{
  Input::AddKey(_k);
}
void Application::KeyboardUp(unsigned char _k, int _x, int _y)
{
  Input::RemoveKey(_k);
}
void Application::MouseMotionPassive(int _x, int _y)
{
  Input::UpdateMouseDelta(_x, _y);
}

void Application::ErrPrint(std::exception _e)
{
  //TODO Some handling of exception printing api here
  std::cerr << std::endl
    << "Run-time Exception:" 
    << std::endl 
    << _e.what() << std::endl;
  throw;
}
void Application::ErrPrint(std::string _msg)
{
  std::cerr << std::endl
    << "Run-time Error:"
    << std::endl
    << _msg.c_str() << std::endl;
}
void Application::ErrPrint(GLchar *_msg)
{
  std::cerr << std::endl
    << "Run-time Error:"
    << std::endl
    << _msg << std::endl;
}

void Application::RecenterMouse()
{
  glutWarpPointer(640, 360);
}