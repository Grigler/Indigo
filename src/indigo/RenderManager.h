#ifndef __IND_RENDER_MANAGER__
#define __IND_RENDER_MANAGER__

#include <memory>

//#include <glm/glm.hpp>

namespace Indigo
{

  class RenderManager
  {
    friend class Environment;
  public:

    static void StartUp(int _argc, char *_argv[]);
    static void StartUp(int _argc, char *_argv[], 
      unsigned int _winX, unsigned int _winY, bool _fullScreenFlag);

    static void ShutDown();
  private:
    //Find how to initialise to nullptr
    static RenderManager *instance;

    RenderManager(int _argc, char *_argv[]);
    RenderManager(int _argc, char *_argv[],
      unsigned int _winX, unsigned int _winY, bool _fullScreenFlag);

    void Draw();
  };

}

#endif