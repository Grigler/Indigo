#include <indigo/indigo.h>

class ObjA : public Indigo::GameObject
{
public:
  ObjA()
  {
    //Messages can be registered on any class derived from memObj
    //(currently only GameObject and Component)
    RegisterMessage("leftMsg", onLeftMsg);
    RegisterMessage("rightMsg", onRightMsg);
    sending = false;
    to = nullptr;
  }
  void Update()
  {
    if (sending && Indigo::Input::GetKey('a'))
    {
      SendMessage(to, "leftMsg");
    }
    else if (sending && Indigo::Input::GetKey('d'))
    {
      SendMessage(to, "rightMsg");
    }
    if (Indigo::Input::GetKey('q'))
    {
      Indigo::Application::ShutDown();
    }
  }

  bool sending;
  ObjA *to;
private:
  static void onLeftMsg(Indigo::MemObj *_m)
  {
    std::printf("Left Message recieved\n");
  }
  static void onRightMsg(Indigo::MemObj *_m)
  {
    std::printf("Right Message recieved\n");
  }

};

int main(int argc, char** argv)
{
  //Intialising Application layer - creating the engineContext
  //Future TODO - Allow specific subsytem initialisation
  //from #define flags
  Indigo::Application::Init(argc, argv);

  //Game code initalisation is executed here
  ObjA a;
  a.sending = true;
  ObjA b;
  a.to = &b;
  //Application gameLoop is executed
  Indigo::Application::Run();
  //Kill is then called for memory cleanup
  Indigo::Application::Kill();
  return 0;
}