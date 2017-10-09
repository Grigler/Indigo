#ifndef __IND_GAME_OBJECT__
#define __IND_GAME_OBJECT__

#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "MemObj.h"

namespace Indigo
{
  class Component;
  class Transform;

  class GameObject : public MemObj
  {
  public:
    GameObject();
    GameObject(Transform _trans, std::shared_ptr<GameObject> *_parent = nullptr);
    GameObject(glm::vec3 _pos, glm::vec3 _rot, std::shared_ptr<GameObject> *_parent = nullptr);

    virtual void Update() {}
    virtual void LateUpdate() {}
    virtual void Draw() {}

    std::shared_ptr<Transform> transform;

  private:
    std::weak_ptr<GameObject> parent;
    std::vector<std::shared_ptr<Component>> components;
  };
}

#endif