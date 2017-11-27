//#define IND_AUDIO_OPENAL
//#define IND_PHYS_IND

#include <indigo/indigo.h>

class TestScript : public Indigo::Component
{
public:

  void onCollision(std::weak_ptr<Indigo::Collision> _col)
  {
    printf("I collided!\n");
  }
};

class ExampleObject : public Indigo::GameObject
{
public:
  
  void onCreation()
  {
    mr = AddComponent<Indigo::MeshRenderer>();
    mr.lock()->LoadMesh("C:/Users/i7465070/Indigo/data/Models/gourd.obj");
    //mr.lock()->LoadMesh("C:/Users/i7465070/Indigo/data/Models/tri.obj");

    transform->SetPosition(glm::vec3(rand()%50 - 25, -25, rand()%50 - 25));
    //transform->SetPosition(glm::vec3(0, 0, 0));
    //printf("Pos %f %f %f\n", transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);
    transform->SetScale(glm::vec3(10.0f, 10.0f, 10.0f));
    sound = Indigo::AudioManager::Load("C:\\Users\\i7465070\\Indigo\\data\\Sounds\\Test Sound.ogg");
    if (p == false)
    {
      sound.lock()->Play();
      p = true;
    }

    rb = AddComponent<Indigo::RB>();
    rb.lock()->AssignCollider(Indigo::ColliderType::Sphere);

    ts = AddComponent<TestScript>();
  }
  void onUpdate()
  {
    transform->SetRotation(transform->GetRotation() + glm::vec3(0,1,0) * Indigo::Application::GetDT());
  }
  void Draw()
  {
    mr.lock()->Draw();
  }

private:
  std::weak_ptr<Indigo::MeshRenderer> mr;
  std::weak_ptr<Indigo::Camera> cam;
  std::weak_ptr<Indigo::Sound> sound;

  std::weak_ptr<Indigo::RB> rb;
  std::weak_ptr<TestScript> ts;

  static bool p;
};
bool ExampleObject::p = false;

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
  
  const int amnt = 10;
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