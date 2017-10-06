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
  //TODO - mouse

  //Init glew
  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}
void Application::Kill()
{
  //Destruction here
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

  Kill();
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

  //Sleep for vsync here

  //Update all objects
  engineContext->Update();

  glutPostRedisplay();

  //Clearing upKeys buffer for next input polling
  Input::upKeys.clear();
}
void Application::Display()
{
  engineContext->Draw();
  /**
  /*Done at this layer so it could be swapped out for
  /*another API if needed - Engine::Draw should
  /*only contain openGL with a given window handle
  **/
  glutSwapBuffers();
}
void Application::Keyboard(unsigned char _k, int _x, int _y)
{
  Input::AddKey(_k);
}
void Application::KeyboardUp(unsigned char _k, int _x, int _y)
{
  Input::RemoveKey(_k);
  //TODO - send up event to message queue
}

void Application::ErrPrint(std::exception _e)
{
  //TODO Some handling of exception printing api here
  std::cerr << std::endl
    << "Run-time Exception:" 
    << std::endl 
    << _e.what() << std::endl;
}
void Application::ErrPrint(std::string _msg)
{
  std::cerr << std::endl
    << "Run-time error:"
    << std::endl
    << _msg.c_str() << std::endl;
}