#ifndef __IND_MESSAGE__
#define __IND_MESSAGE__

#include <memory>
#include <string>

namespace Indigo
{

  class MemObj;

  struct Message
  {
    std::weak_ptr<MemObj> from;
    std::weak_ptr<MemObj> to;
    std::string msg;
  };

}
#endif