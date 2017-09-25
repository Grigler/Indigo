#ifndef __IND_SCENE__
#define __IND_SCENE__

#include <memory>

namespace Indigo
{

  class LinkedList;

  class Scene
  {
  public:

    void tick(float _dtS);

  private:

    std::unique_ptr<LinkedList> topLevel;

  };

} //End of namespace

#endif