#ifndef __IND_MEM_OBJ__
#define __IND_MEM_OBJ__

namespace Indigo
{
  class MemObj
  {
    friend class Engine;
  public:
    MemObj();

    void MarkToKill();
  private:
    bool readyToDestroy;
  };
}

#endif