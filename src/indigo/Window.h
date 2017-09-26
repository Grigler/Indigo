#ifndef __IND_WINDOW__
#define __IND_WINDOW__

#include "GL/glew.h"
#include <string>

namespace Indigo
{

  class Window
  {
  public:

  private:
    GLint handle;

    std::string name;
  };

} //End of namespace

#endif