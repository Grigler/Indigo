#include "config.h"
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
      if (rb.lock()->GetLinearVel() != glm::vec3(0.0f))
      {
        printf("Force Applied\n");
        rb.lock()->ApplyForceAtLocation(glm::vec3(0.0f, 0.0f, 1000.0f),
          glm::vec3(0.0f, 1.0f, 0.0f));
      }
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
    if (p == true)
    {
      mr.lock()->LoadMesh("./data/Models/sphere.obj");
      transform->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
    }
    else
    {
      mr.lock()->LoadMesh("./data/Models/plane.obj");
      transform->SetScale(glm::vec3(25.0f, 2.5f, 2.5f));
    }

    rb = AddComponent<Indigo::RB>();

    //transform->SetPosition(glm::vec3(rand()%50 - 25, 0.0f, rand()%100 + 50));
    if (p == false)
    {
      transform->SetPosition(glm::vec3(0.0f, -4.0f, 10.0f));
      rb.lock()->AssignCollider(Indigo::ColliderType::Plane);
      rb.lock()->SetGravity(false);
      //Arbitrarily large mass and inertia for static object
      rb.lock()->SetMass(5000000.0f);
      //rb.lock()->SetInertiaTensor(glm::mat3(1.0));
      p = true;
    }
    else
    {
      //transform->SetPosition(glm::vec3(0.0f, 2.5f, 10.0f));
      rb.lock()->SetMass(15.0f);
      rb.lock()->SetGravity(true);

      l = AddComponent<Indigo::Light>();
      l.lock()->SetColour(glm::vec3(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f));
    }
    
    //sound = Indigo::AudioManager::Load("C:\\Users\\i7465070\\Indigo\\data\\Sounds\\Test Sound.ogg");
    if (p == false)
    {
      //sound.lock()->Play();
      p = true;
    }
    
    ts = AddComponent<TestScript>();
  }
  void onUpdate()
  {
    if (Indigo::Input::GetKeyDown(' ') && mr.lock()->mesh->GetVertCount() == 600)
    {
      std::weak_ptr<ExampleObject> e =
        Indigo::GameObject::CreateGameObject<ExampleObject>();
      e.lock()->transform->SetPosition(glm::vec3(1.0f, 1.5f, 10.0f));
      e.lock()->GetComponent<Indigo::RB>().lock()->ApplyForceAtLocation(glm::vec3(rand()%20000-10000, rand()%400 - 800, 0.0f),
        glm::vec3(0));
    }
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

  std::weak_ptr<Indigo::Light> l;

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

    l = AddComponent<Indigo::Light>();
    l.lock()->SetColour(glm::vec3(0.75f, 0.0f, 0.0f));
  }
  void onUpdate()
  {
    //printf("DT: %f\n", Indigo::Application::GetDT());
  }

  std::weak_ptr<Indigo::CharacterController> cc;
  std::weak_ptr<Indigo::Light> l;
};


int main(int argc, char** argv)
{
  glm::vec3 dv = glm::vec3(0, 2, 0);
  glm::vec3 n = glm::vec3(0, -1, 0);
  glm::vec3 c = glm::cross(dv, n);
  float d = glm::dot(dv, n);

  printf("C: %f, %f, %f\nD: %f\n", c.x, c.y, c.z, d);

  Indigo::Application::Init(argc, argv);

  std::weak_ptr<CamObject> co = Indigo::GameObject::CreateGameObject<CamObject>();
  
  const int amnt = 2;
  std::weak_ptr<ExampleObject> eoArr[amnt];

  for (int i = 0; i < amnt; i++)
  {
    eoArr[i] = Indigo::GameObject::CreateGameObject<ExampleObject>();
    if (i != 0)
    {
      eoArr[i].lock()->transform->SetPosition(glm::vec3(1.0f, i * 1.5f, 10.0f));
      //eoArr[i].lock()->GetComponent<Indigo::RB>().lock()->ApplyForceAtLocation(glm::vec3(-1000000.0f, -1000000.0f, 0.0f),
      //  glm::vec3(0));
    }
    printf("Num: %i\n", i + 1);
  }

  //Application gameLoop is executed
  //glViewport(0, 0, 1280, 720);
  Indigo::Application::Run();
  //Kill is then called for memory cleanup
  Indigo::Application::Kill();

  return 0;
}