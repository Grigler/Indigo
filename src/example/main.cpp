#include <indigo/indigo.h>

class ExampleObject : public Indigo::GameObject
{
public:
  ExampleObject()
  {
    mr = AddComponent<Indigo::MeshRenderer>();

    mr.lock()->LoadMesh("This Doesn't matter yet");

  }
  void Update()
  {

  }
  void Draw()
  {
    mr.lock()->Draw();
  }

private:

  std::weak_ptr<Indigo::MeshRenderer> mr;

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

  std::shared_ptr<ExampleObject> eo = std::make_shared<ExampleObject>();

  //Application gameLoop is executed
  Indigo::Application::Run();
  //Kill is then called for memory cleanup
  Indigo::Application::Kill();

  return 0;
}