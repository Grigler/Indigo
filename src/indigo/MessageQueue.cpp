#include "MessageQueue.h"

using namespace Indigo;

void MessageQueue::SendAll()
{
  for(std::list<Message*>::iterator i = msgQueue.begin();
    i != msgQueue.end(); i++)
  {
    Send((*i));
  }
}