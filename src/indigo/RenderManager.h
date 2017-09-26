#ifndef __IND_RENDER_MANAGER__
#define __IND_RENDER_MANAGER__

#include <memory>

#include <glm/glm.hpp>

namespace Indigo
{

  class RenderManager
  {
  public:

    static void StartUp(int _argc, char *_argv[]);
    static void StartUp(int _argc, char *_argv[], 
      glm::vec2 _winSize, bool _fullScreenFlag);

  private:
    //Find how to initialise to nullptr
    static RenderManager *instance;

    RenderManager(int _argc, char *_argv[]);
    RenderManager(int _argc, char *_argv[],
      glm::vec2 _winSize, bool _fullScreenFlag);
  };

}

#endif