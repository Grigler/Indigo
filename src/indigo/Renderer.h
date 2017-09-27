#ifndef __IND_RENDERER__
#define __IND_RENDERER__

#include <list>

namespace Indigo
{

  class Camera;
  class GameObj;

  class Renderer
  {
  public:
    void Render(Camera *_cam, std::list<GameObj*> _allObjs);

  private:
    static Camera *currentCam;
    //Used for sorting objs by distance
    static bool closestFirst(GameObj *l, GameObj *r);
  };

}

#endif