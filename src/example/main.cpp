#include <indigo/indigo.h>

class ExampleObject : public Indigo::GameObject
{
public:
  void onCreation()
  {
    mr = AddComponent<Indigo::MeshRenderer>();
    mr.lock()->LoadMesh("C:/Users/i7465070/Indigo/data/Models/teapot.obj");
    //mr.lock()->LoadMesh("C:/Users/i7465070/Indigo/data/Models/tri.obj");

    transform->SetPosition(glm::vec3(rand()%1000 - 500, -20, rand()%1000 - 500));
    //printf("Pos %f %f %f\n", transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);
    transform->SetScale(glm::vec3(0.125f, 0.125f, 0.125f));
  }
  void onUpdate()
  {
    transform->SetRotation(transform->GetRotation() + glm::vec3(0,1,0) * Indigo::Application::GetDT());
    /*
    glm::vec3 moveVec = glm::vec3(0);
    std::weak_ptr<Indigo::Transform> t = transform;
    if (Indigo::Input::GetKey('w') || Indigo::Input::GetKey('W'))
    {
      moveVec += t.lock()->GetForward() * 150.0f;
    }
    if (Indigo::Input::GetKey('s') || Indigo::Input::GetKey('S'))
    {
      moveVec += t.lock()->GetForward() * -150.0f;
    }

    if (Indigo::Input::GetKey('e') || Indigo::Input::GetKey('E'))
    {
      moveVec += t.lock()->GetRight() * 150.0f;
    }
    if (Indigo::Input::GetKey('q') || Indigo::Input::GetKey('Q'))
    {
      moveVec += t.lock()->GetRight() * -150.0f;
    }

    t.lock()->SetPosition(t.lock()->GetPosition() + moveVec * Indigo::Application::GetDT());
    */
  }
  void Draw()
  {
    mr.lock()->Draw();
  }

private:
  std::weak_ptr<Indigo::MeshRenderer> mr;
  std::weak_ptr<Indigo::Camera> cam;

};

class CamObject : public Indigo::GameObject
{
public:
  std::weak_ptr<Indigo::Camera> cam;
  void onCreation()
  {
    cc = AddComponent<Indigo::CharacterController>();
    cc.lock()->moveSpeed = 150.0f;
    cc.lock()->mouseSens = glm::vec2(1.0f, 1.0f);

    cam = AddComponent<Indigo::Camera>();
    //cam.lock()->MakeActive();
    Indigo::Camera::currentActive = cam;
  }

  std::weak_ptr<Indigo::CharacterController> cc;
};


int main(int argc, char** argv)
{
  Indigo::Application::Init(argc, argv);
  
  std::weak_ptr<CamObject> co = Indigo::GameObject::CreateGameObject<CamObject>();
  
  const int amnt = 200;
  std::weak_ptr<ExampleObject> eoArr[amnt];

  for (int i = 0; i < amnt; i++)
  {
    eoArr[i] = Indigo::GameObject::CreateGameObject<ExampleObject>();
    printf("Num: %i\n", i + 1);
  }

  //Application gameLoop is executed
  glViewport(0, 0, 1280, 720);
  Indigo::Application::Run();
  //Kill is then called for memory cleanup
  Indigo::Application::Kill();

  return 0;
}