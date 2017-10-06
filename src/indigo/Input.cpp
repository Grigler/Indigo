#include "Input.h"

#include "Application.h"

using namespace Indigo;
//Both have 10 spaces allocated initially
std::vector<unsigned char> Input::keys(10);
std::vector<unsigned char> Input::upKeys(10);

bool Input::GetKey(unsigned char _k)
{
  for (auto i = keys.begin(); i != keys.end(); i++)
  {
    if ((*i) == _k) return true;
  }
  return false;
}
bool Input::GetKeyUp(unsigned char _k)
{
  for (auto i = upKeys.begin(); i != upKeys.end(); i++)
  {
    if ((*i) == _k) return true;
  }
  return false;
}

void Input::AddKey(unsigned char _k)
{
  //Checking for duplicates
  for (auto i = keys.begin(); i != keys.end(); i++)
  {
    if ((*i) == _k) return;
  }

  keys.push_back(_k);
}
void Input::RemoveKey(unsigned char _k)
{
  for (auto i = keys.begin(); i != keys.end(); i++)
  {
    if ((*i) == _k)
    {
      keys.erase(i);
      //Simple push_back as multiple RemoveKey events
      //should never happen
      upKeys.push_back(_k);
      return;
    }
  }
}