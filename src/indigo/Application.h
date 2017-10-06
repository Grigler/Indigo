#ifndef __IND_APPLICATION__
#define __IND_APPLICATION__

#include <memory>
#include <string>

namespace Indigo
{

  class Engine;

  class Application
  {
    friend class Engine;
  public:

    static void Init(int _argc, char* _argv[]);
    static void Kill();

    static void Run();

    static float GetDT();

  private:
    static std::shared_ptr<Engine> engineContext;

    static void Idle();
    static void Display();
    static void Keyboard(unsigned char _k, int _x, int _y);
    static void KeyboardUp(unsigned char _k, int _x, int _y);

    static float deltaTime;

    static void ErrPrint(std::exception _e);
    static void ErrPrint(std::string _msg);
  };

}

#endif