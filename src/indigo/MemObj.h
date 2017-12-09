#ifndef __IND_MEM_OBJ__
#define __IND_MEM_OBJ__

#define STRINGIFY(A) #A

#include <memory>
#include <string>
#include <vector>
#include <map>
/*
namespace Indigo
{
  class MemObj;
  struct message;

  struct MessageReg
  {
    std::string msg;
    void (*callback)(MemObj *from);
  };

  class MemObj
  {
    friend class Engine;
  public:
    MemObj();

    void MarkToKill();

    void SendMessage(MemObj *_to, std::string _msg);
    void RecieveMessage(std::string _msg, std::weak_ptr<MemObj> _from);
  protected:
    std::vector<std::string> registeredMessages;
    //Used to register a message string to a function
    //this function will be ran with the msg sender as an argument
    void RegisterMessage(std::string _msg, void(call)(MemObj *from));
  private:
    bool readyToDestroy;
    std::vector<MessageReg> messageRegister;

  };
}
*/


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

    static std::map<std::string, std::weak_ptr<MemObj>> listeners;


  };

}

#endif