#include "MemObj.h"

using namespace Indigo;

MemObj::MemObj()
{
  readyToDestroy = true;
}

void MemObj::MarkToKill()
{
  readyToDestroy = true;
}