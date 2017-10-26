#ifndef __IND_TRANSFORM__
#define __IND_TRANSFORM__

#include "Component.h"
#include "AABB.h"

#include <memory>

#include <glm/glm.hpp>

namespace Indigo
{
  class GameObject;

  class Transform : public Component
  {
    friend class Engine;
  public:
    Transform() { pos = glm::vec3(0); rot = glm::vec3(0); scale = glm::vec3(1); }
    Transform(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);

    glm::vec3 GetPosition() { return pos; }
    glm::vec3 GetRotation() { return rot; }
    glm::vec3 GetScale() { return scale; }
    void SetPosition(glm::vec3 _p) { pos = _p; }
    void SetRotation(glm::vec3 _r) { rot = _r; }
    void SetScale(glm::vec3 _s) { scale = _s; }

    glm::vec3 GetForward();
    glm::vec3 GetUp();
    glm::vec3 GetRight();

    //Updates viewMatrix and returns it
    glm::mat4 GetModelMat();

    void Translate(glm::vec3 _by);
    void MoveTo(glm::vec3 _target, float _alpha);
    void MoveDir(glm::vec3 _dir, float _alpha);

    void Rotate(glm::vec3 _eulerAngles);
    //Multiplies each axis by xyz components of param
    void Scale(glm::vec3 _scaleBy);

    void onUpdate();

    bool _CheckForAABBRecalc() { return _aabbNeedRecalc; }

  private:
    glm::vec3 pos;
    //Euler angles
    glm::vec3 rot;
    glm::vec3 scale;

    glm::mat4 modelMat;

    //Transforms rotation vec to mat4
    glm::mat4 _RotVecToMat();
    //Keeps track of scale/rot changes per frame
    //can then be requested by mesh/AABB for recalc logic
    bool _aabbNeedRecalc;
  };
}

#endif