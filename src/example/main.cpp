#include "config.h"
#include <indigo/indigo.h>


class CamObject : public Indigo::GameObject
{
public:
  void onCreation()
  {
    transform->SetPosition(glm::vec3(0.0f, 0.0f, -20.0f));
    cc = AddComponent<Indigo::CharacterController>();
    cc.lock()->moveSpeed = 8.0f;
    cc.lock()->mouseSens = glm::vec2(0.05f, 0.05f);

    cam = AddComponent<Indigo::Camera>();
    Indigo::Camera::currentActive = cam;

    std::shared_ptr<Indigo::Light> l = AddComponent<Indigo::Light>().lock();
    l->SetColour(glm::vec3(0.4f, 0.4f, 0.4f));
  }
  void onUpdate()
  {
    //printf("DT: %f\n", Indigo::Application::GetDT());
    if (Indigo::Input::GetKeyDown('p'))
    {
      printf("Position: %f, %f, %f\n",
        transform->GetPosition().x,
        transform->GetPosition().y,
        transform->GetPosition().z);
      printf("Rotation: %f, %f, %f\n",
        transform->GetRotation().x,
        transform->GetRotation().y,
        transform->GetRotation().z);
      printf("Forward: %f, %f, %f\n",
        transform->GetForward().x,
        transform->GetForward().y,
        transform->GetForward().z);
      printf("Up: %f, %f, %f\n",
        transform->GetUp().x,
        transform->GetUp().y,
        transform->GetUp().z);
      printf("Right: %f, %f, %f\n\n",
        transform->GetRight().x,
        transform->GetRight().y,
        transform->GetRight().z);
    } 

    if (Indigo::Input::GetKeyUp(' '))
    {
      BroadCastMessage("Space", cam);
    }
  }
  std::weak_ptr<Indigo::Camera> cam;
  std::weak_ptr<Indigo::CharacterController> cc;
};

class VoidSphere : public Indigo::GameObject
{
public:
  void onCreation()
  {
    mr = AddComponent<Indigo::MeshRenderer>();
    mr.lock()->LoadMesh("./data/Models/sphere.obj");
    mr.lock()->LoadTexture("./data/Textures/brick.png");
  }

  void onLateUpdate()
  {
    drawnVoidSpheres = 0;
  }

  void Draw()
  {
    drawnVoidSpheres++;
    mr.lock()->Draw();
  }

  static int drawnVoidSpheres;

  std::weak_ptr<Indigo::MeshRenderer> mr;
};
int VoidSphere::drawnVoidSpheres = 0;
class VoidScene : public Indigo::GameObject
{

public:
  void onCreation()
  {
    const int size = 150;
    spheres.reserve(size*size*size);

    for (int x = -size; x < size; x += 10)
    {
      printf("%i\n", x);
      for (int y = -size; y < size; y += 10)
      {
        for (int z = -size; z < size; z += 10)
        { 
          spheres.push_back(CreateGameObject<VoidSphere>());
          spheres.back().lock()->transform->SetPosition(glm::vec3(x, y, z));
        }
      }
    }

    co = Indigo::GameObject::CreateGameObject<CamObject>();
    co.lock()->transform->SetPosition(glm::vec3(0));
  }

  std::vector<std::weak_ptr<Indigo::GameObject>> spheres;
  std::weak_ptr<CamObject> co;
};

class BeachBall : public Indigo::GameObject
{
public:

  void onCreation()
  {
    mr = AddComponent<Indigo::MeshRenderer>();

    mr.lock()->LoadMesh("./data/Models/sphere.obj");
    mr.lock()->LoadTexture("./data/Textures/BeachBallColor.png");
    transform->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

    rb = AddComponent<Indigo::RB>();

    rb.lock()->SetMass(5.0f);
    rb.lock()->SetGravity(true);

    l = AddComponent<Indigo::Light>();
    l.lock()->SetColour(glm::vec3(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f));
    l.lock()->SetAttenuation(1.0f);
  }
  void Draw()
  {
    mr.lock()->Draw();
  }

private:
  std::weak_ptr<Indigo::MeshRenderer> mr;
  std::weak_ptr<Indigo::Camera> cam;

  std::weak_ptr<Indigo::RB> rb;

  std::weak_ptr<Indigo::Light> l;
};
class PlaneWall : public Indigo::GameObject
{
public:
  void onCreation()
  {
    mr = AddComponent<Indigo::MeshRenderer>();
    mr.lock()->LoadMesh("./data/Models/plane.obj");
    mr.lock()->LoadTexture("./data/Textures/brick.png");
    transform->SetScale(glm::vec3(25.0f, 25.0f, 25.0f));

    std::weak_ptr<Indigo::RB> rb = AddComponent<Indigo::RB>();
    rb.lock()->AssignCollider(Indigo::ColliderType::Plane);
    rb.lock()->SetGravity(false);
    //Arbitrarily large mass and inertia for static object
    rb.lock()->SetMass(5000000.0f);

    
  }

  void Draw()
  {
    mr.lock()->Draw();
  }
  std::weak_ptr<Indigo::MeshRenderer> mr;
};
class FireScript : public Indigo::Component
{
public:
  void onUpdate()
  {
    if (Indigo::Input::GetKeyDown('f') || Indigo::Input::GetKeyDown('F'))
    {
      Fire();
    }
  }
  void Fire()
  {
    std::weak_ptr<BeachBall> b = Indigo::GameObject::CreateGameObject<BeachBall>();
    b.lock()->transform->SetPosition(transform->GetPosition()+transform->GetForward()*0.5f);
    b.lock()->transform->SetRotation(transform->GetRotation());
    b.lock()->GetComponent<Indigo::RB>().lock()->ApplyForceAtLocation(
      transform->GetForward() * 10000.0f, glm::vec3(0.0f, -0.1f, 0.0f));
  }
};
class DemoScene : public Indigo::GameObject
{
public:
  void onCreation()
  {
    std::weak_ptr<CamObject> camObj = CreateGameObject<CamObject>();
    camObj.lock()->transform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    camObj.lock()->AddComponent<FireScript>();

    std::weak_ptr<PlaneWall> pwFloor = CreateGameObject<PlaneWall>();
    pwFloor.lock()->transform->SetPosition(glm::vec3(0.0f, -2.5f, 0.0f));

    std::weak_ptr<Indigo::Sound> bgMusic = Indigo::AudioManager::Load("./data/Sounds/funkyBG.ogg");
    bgMusic.lock()->Play();

    spawnSound = Indigo::AudioManager::Load("./data/Sounds/warp.ogg");
  }

  void onUpdate()
  {
    timer -= Indigo::Application::GetDT();
    if (timer <= 0.0f)
    {
      spawnSound.lock()->PlayWithVariance(0.25f, 0.75f);
      std::weak_ptr<BeachBall> b = Indigo::GameObject::CreateGameObject<BeachBall>();
      b.lock()->transform->SetPosition(glm::vec3((rand() % 20 - 10) / 10.0f, 7.5f, (rand() % 20 - 10) / 10.0f));
      b.lock()->GetComponent<Indigo::RB>().lock()->ApplyForceAtLocation(
        glm::vec3(((rand() % 20 - 10) / 10.0f), ((rand() % 20 - 10) / 10.0f), ((rand() % 20 - 10) / 10.0f)) * 5000.0f,
        glm::vec3(0.0f, -0.1f, 0.0f));

      timer = 1.5f;
    }
  }

  std::weak_ptr<Indigo::Sound> spawnSound;

  float timer = 1.5f;
};

int main(int argc, char** argv)
{
  Indigo::Application::Init(argc, argv);

  //std::weak_ptr<VoidScene> scene = Indigo::GameObject::CreateGameObject<VoidScene>();

  std::weak_ptr<DemoScene> scene = Indigo::GameObject::CreateGameObject<DemoScene>();

  //Application gameLoop is executed
  Indigo::Application::Run();
  //Kill is then called for memory cleanup
  Indigo::Application::Kill();

  return 0;
}