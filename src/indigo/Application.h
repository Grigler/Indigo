#ifndef __IND_APPLICATION__
#define __IND_APPLICATION__

#include <memory>
#include <string>
#include <GL/glew.h>

namespace Indigo
{

  class Engine;

  class Application
  {
    friend class Engine;
    friend class MemObj;
    friend class GameObject;
    friend class Camera;
  public:

    static void Init(int _argc, char* _argv[]);
    //Called Manually after Run() is finished
    //Should NOT be called during mainLoop
    static void Kill();
    //Call to exit glutMainLoop (or equivalent)
    static void ShutDown();
    //Called to enter the mainLoop
    static void Run();

    static float GetDT();

    static void ErrPrint(std::exception _e);
    static void ErrPrint(std::string _msg);
    static void ErrPrint(GLchar *_msg);

    static void RecenterMouse();

  private:
    static std::shared_ptr<Engine> engineContext;

    static void Idle();
    static void Display();
    static void Keyboard(unsigned char _k, int _x, int _y);
    static void KeyboardUp(unsigned char _k, int _x, int _y);
    static void MouseMotionPassive(int _x, int _y);

    static float deltaTime;
    static float fixedTime;
  };

}

#endif