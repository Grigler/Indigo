#include "MemObj.h"

#include "Application.h"
#include "Engine.h"

#include "message.h"

using namespace Indigo;

std::map<std::string, std::weak_ptr<MemObj>> MemObj::listeners;

void MemObj::BroadCastMessage(std::string _msg, std::weak_ptr<MemObj> _sender)
{
  for (auto i = listeners.begin(); i != listeners.end(); i++)
  {
    if (i->first == _msg)
    {
      i->second.lock()->RecieveMessage(_msg, _sender);
    }
  }
}

void MemObj::ListenForMessage(std::string _msg, std::weak_ptr<MemObj> _this)
{
  std::pair<std::string, std::weak_ptr<MemObj>> p(_msg, _this);
  listeners.insert(listeners.end(), p);
}
void MemObj::StopListeningFor(std::string _msg, std::weak_ptr<MemObj> _this)
{
  for (auto i = listeners.begin(); i != listeners.end(); i++)
  {
    if (i->second.lock().get() == _this.lock().get())
    {
      if(i->first == _msg)
        listeners.erase(i);
    }
  }
}