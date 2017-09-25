#ifndef __IND_MESSAGE_QUEUE__
#define __IND_MESSAGE_QUEUE__

#include <memory>
#include <list>
#include <map>

namespace Indigo
{

  //TODO - plan how messages are created and sent - specifically
  //how the message queue is referenced from the gameObj
  //and how the message is added to it

  class GameObj;

  struct Message
  {
    GameObj *from;
    GameObj *to;
    std::string message;
    //Some kind of payload structure for necessary vars? maybe a map

    Message(GameObj *_from, GameObj *_to, std::string _message)
    {
      from = _from; to = _to; message = _message;
      if(from == nullptr || to == nullptr) throw std::exception();
    }
  };

  class MessageQueue
  {
  public:
    std::list<Message*> msgQueue;
    
    void SendAll();

  private:
    void Send(Message *msg);
  };

} //End of namespace

#endif