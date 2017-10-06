#include "MemObj.h"

#include "Application.h"
#include "Engine.h"

#include "message.h"

using namespace Indigo;

MemObj::MemObj()
{
  readyToDestroy = true;
  Application::engineContext->RegisterMemObj(this);
}

void MemObj::MarkToKill()
{
  readyToDestroy = true;
}

void MemObj::SendMessage(MemObj *_to, std::string _msg)
{
  Message m;
  m.from = Application::engineContext->GetMemObjRef(this);
  m.to = Application::engineContext->GetMemObjRef(_to);
  m.msg = _msg;
  Application::engineContext->RegisterMsg(m);
}
void MemObj::RecieveMessage(std::string _msg, std::weak_ptr<MemObj> _from)
{
  for (auto i = messageRegister.begin(); i != messageRegister.end(); i++)
  {
    if ((*i).msg == _msg)
    {
      (*i).callback(_from.lock().get());
      return;
    }
  }
  Application::ErrPrint("No message registered for " + _msg);
}
void MemObj::RegisterMessage(std::string _msg, void(call)(MemObj *from))
{
  for (auto i = messageRegister.begin(); i != messageRegister.end(); i++)
  {
    if ((*i).msg == _msg)
    {
      Application::ErrPrint("Multiple message instance for " + _msg);
      return;
    }
  }
  MessageReg mr;
  mr.msg = _msg;
  mr.callback = call;

  messageRegister.push_back(mr);
}