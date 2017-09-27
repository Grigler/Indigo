#ifndef __IND_WINDOW__
#define __IND_WINDOW__

#include "GL/glew.h"
#include <string>

namespace Indigo
{

  class Window
  {
  public:
    //Registers/Unregisters self with rendermanager
    Window(std::string _name, int _w, int _h);
    ~Window();

    void Reshape(int _w, int _h);
    bool isActive;

  private:
    GLint handle;

    int winWidth, winHeight;

    std::string name;
  };

} //End of namespace

#endif