#ifndef __IND_RENDER_MANAGER__
#define __IND_RENDER_MANAGER__

#include <memory>
#include <list>

namespace Indigo
{

  class Camera;

  class RenderManager
  {
    friend class Environment;
    friend class Camera;
  public:

    static void StartUp(int _argc, char *_argv[]);
    static void StartUp(int _argc, char *_argv[], 
      unsigned int _winX, unsigned int _winY, bool _fullScreenFlag);

    static void ShutDown();
    
  private:
    static RenderManager *instance;

    RenderManager(int _argc, char *_argv[]);
    RenderManager(int _argc, char *_argv[],
      unsigned int _winX, unsigned int _winY, bool _fullScreenFlag);

    void Draw();

    std::list<Camera*> cameraRegister;
    static void RegisterCamera(Camera *_c);
    static void UnregisterCamera(Camera *_c);
  };

}

#endif