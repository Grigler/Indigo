#include <indigo/indigo.h>

class ExampleObject : public Indigo::GameObject
{
public:
  ExampleObject()
  {
    //Messages can be registered on any class derived from memObj
    //(currently only GameObject and Component)
    //RegisterMessage("leftMsg", onLeftMsg);
    //RegisterMessage("rightMsg", onRightMsg);
    sending = false;
    to = nullptr;
  }
  void Update()
  {
    if (sending && Indigo::Input::GetKey('a'))
    {
      //SendMessage(to, "leftMsg");
    }
    else if (sending && Indigo::Input::GetKey('d'))
    {
      //SendMessage(to, "rightMsg");
    }

    if (Indigo::Input::GetKey('q'))
    {
      Indigo::Application::ShutDown();
    }
  }

  bool sending;
  ExampleObject *to;

private:
  //This could handle any interaction with _m
  static void onLeftMsg(Indigo::MemObj *_m)
  {
    std::printf("Left Message recieved\n");
  }
  static void onRightMsg(Indigo::MemObj *_m)
  {
    std::printf("Right Message recieved\n");
  }
};

class NotDerived
{
public:
  int a;
};
class SomeComp : public Indigo::Component
{
public:

  void Update()
  {
    printf("\tSomeComp Update\n");
  }
};

int main(int argc, char** argv)
{
  //Intialising Application layer - creating the engineContext
  //Future TODO - Allow specific subsytem initialisation
  //from #define flags
  Indigo::Application::Init(argc, argv);

  //std::weak_ptr<ExampleObject> a = Indigo::GameObject::CreateGameObject<ExampleObject>();
  //a.lock()->sending = true;

  //a.lock()->AddComponent<SomeComp>();
  //a.lock()->AddComponent<Indigo::Transform>();

  //Causes compile error - as it should
  //std::weak_ptr<NotDerived> b = Indigo::GameObject::CreateGameObject<NotDerived>();

  //Application gameLoop is executed
  Indigo::Application::Run();
  //Kill is then called for memory cleanup
  Indigo::Application::Kill();

  return 0;
}