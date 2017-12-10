#ifndef __IND_MEM_OBJ__
#define __IND_MEM_OBJ__

#define STRINGIFY(A) #A

#include <memory>
#include <string>
#include <vector>

namespace Indigo
{

  //Used for handling messages
  class MemObj
  {
    friend class Engine;
    friend class GameObject;
  public:

    void BroadCastMessage(std::string _msg, std::weak_ptr<MemObj> _sender);
    virtual void RecieveMessage(std::string _msg, std::weak_ptr<MemObj> _sender) {}

    void ListenForMessage(std::string _msg, std::weak_ptr<MemObj> _this);
    void StopListeningFor(std::string _msg, std::weak_ptr<MemObj> _this);

    //Format of listener is [msg key | ptr to listener] as a pair
    static std::vector<std::pair<std::string, std::weak_ptr<MemObj>>> listeners;


  };

}

#endif