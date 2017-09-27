#ifndef __IND_RENDER_MANAGER__
#define __IND_RENDER_MANAGER__

#include <memory>
#include <list>


namespace Indigo
{

  class Camera;
  class Window;

  class RenderManager
  {
    friend class Environment;
    friend class Camera;
    friend class Window;
  public:

    static void StartUp(int _argc, char *_argv[]);
    static void ShutDown();
    //static void CreateWindow(std::string _name, int _w, int _y);
    static void SpawnWindow(std::string _name, int _w, int _h);

  private:
    static RenderManager *instance;

    RenderManager(int _argc, char *_argv[]);

    static void Draw();

    std::list<Camera*> cameraRegister;
    static void RegisterCamera(Camera *_c);
    static void UnregisterCamera(Camera *_c);

    std::list<Window*> windowRegister;
    static void RegisterWindow(Window *_w);
    static void UnregisterWindow(Window *_w);
  };

}

#endif