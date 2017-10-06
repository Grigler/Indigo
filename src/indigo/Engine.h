#ifndef __IND_ENGINE__
#define __IND_ENGINE__

#include <memory>

namespace Indigo
{
  class Engine
  {
    friend class Application;

  public:

  private:
    void Update();
    void Draw();
  };
}
#endif