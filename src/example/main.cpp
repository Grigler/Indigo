#include <indigo/indigo.h>

class TestScript : public Indigo::Component
{
public:
  /*
  void onCollision(std::weak_ptr<Indigo::Collision> _col)
  {
    printf("I collided!\n");
  }
  */
  void onCreation()
  {
    rb = parent.lock()->GetComponent<Indigo::RB>();
    //rb.lock()->SetGravity(false);
  }

  void onUpdate()
  {
    if (Indigo::Input::GetKeyDown('f'))
    {
      rb.lock()->ApplyForceAtLocation(
        glm::vec3(0.0f, -200.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f));
    }
  }
  std::weak_ptr<Indigo::RB> rb;
};

class ExampleObject : public Indigo::GameObject
{
public:
  
  void onCreation()
  {
    mr = AddComponent<Indigo::MeshRenderer>();
    mr.lock()->LoadMesh("C:/Users/i7465070/Indigo/data/Models/sphere.obj");

    rb = AddComponent<Indigo::RB>();

    //transform->SetPosition(glm::vec3(rand()%50 - 25, 0.0f, rand()%100 + 50));
    if (p == false)
    {
      transform->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
      rb.lock()->AssignCollider(Indigo::ColliderType::Plane);
      rb.lock()->SetGravity(false);
      rb.lock()->SetMass(std::numeric_limits<float>::max());
      p = true;
    }
    else
    {
      transform->SetPosition(glm::vec3(0.0f, 2.5f, 10.0f));
      rb.lock()->SetGravity(true);
    }

    transform->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
    /*
    sound = Indigo::AudioManager::Load("C:\\Users\\i7465070\\Indigo\\data\\Sounds\\Test Sound.ogg");
    if (p == false)
    {
      sound.lock()->Play();
      p = true;
    }
    */
    

    ts = AddComponent<TestScript>();
  }
  void onUpdate()
  {
    //transform->SetRotation(transform->GetRotation() + glm::vec3(0,1,0) * Indigo::Application::GetDT());
    glm::vec3 r = transform->GetRotation();
    glm::vec3 v = rb.lock()->GetLinearVel();
    glm::vec3 a = rb.lock()->GetAngularVel();
    //printf("R: %f, %f, %f\n", r.x, r.y, r.z);
    //printf("V: %f, %f, %f\n", v.x, v.y, v.z);
    //printf("A: %f, %f, %f\n\n", a.x, a.y, a.z);
  }
  void Draw()
  {
    mr.lock()->Draw();
  }

private:
  std::weak_ptr<Indigo::MeshRenderer> mr;
  std::weak_ptr<Indigo::Camera> cam;
  //std::weak_ptr<Indigo::Sound> sound;

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
    cc.lock()->moveSpeed = 1.5f;
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
  
  const int amnt = 2;
  std::weak_ptr<ExampleObject> eoArr[amnt];

  for (int i = 0; i < amnt; i++)
  {
    eoArr[i] = Indigo::GameObject::CreateGameObject<ExampleObject>();
    printf("Num: %i\n", i + 1);
  }

  //eoArr[0].lock()->GetComponent<Indigo::RB>().lock()->ApplyForceAtLocation(glm::vec3(0.0f, 0.0f, 100.0f),
  //  glm::vec3(0.0f, 5.0f, 0.0f));
  //eoArr[0].lock()->GetComponent<Indigo::RB>().lock()->ApplyTorque(glm::vec3(-500.0f, 0.0f, 0.0f));
  //eoArr[0].lock()->GetComponent<Indigo::RB>().lock()->ApplyForceAtLocation(
  //  glm::vec3(0.0f, 0.0f, 200000.0f),
  //  glm::vec3(0.0f, 0.5f, 0.0f));

  //eoArr[0].lock()->GetComponent<Indigo::RB>().lock()->SetGravity(false);
  //eoArr[0].lock()->GetComponent<Indigo::RB>().lock()->ApplyForceAtLocation(
  //  glm::vec3(0.0f, 50000.0f, 0.0f),
  //  glm::vec3(0.0f));
  eoArr[1].lock()->GetComponent<Indigo::RB>().lock()->ApplyForceAtLocation(
    glm::vec3(0.0f, -500000.0f, 0.0f),
    glm::vec3(0.0f));


  //Application gameLoop is executed
  //glViewport(0, 0, 1280, 720);
  Indigo::Application::Run();
  //Kill is then called for memory cleanup
  Indigo::Application::Kill();

  return 0;
}