#include <indigo/indigo.h>

class ObjA : public Indigo::GameObject
{
public:
  ObjA()
  {
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
  Indigo::Application::Init(argc, argv);

  ObjA a;
  a.sending = true;
  ObjA b;
  a.to = &b;

  Indigo::Application::Run();

  std::printf("Sending msg\n");
  b.SendMessage(&a, "testMsg");
  std::printf("Sent msg\n");

  

  return 0;
}