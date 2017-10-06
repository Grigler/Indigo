#ifndef __IND_MEM_OBJ__
#define __IND_MEM_OBJ__

#include <memory>
#include <string>
#include <vector>


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

#endif