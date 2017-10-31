#include "Input.h"

#include "Application.h"

using namespace Indigo;

std::vector<unsigned char> Input::keys;
std::vector<unsigned char> Input::upKeys;
std::vector<unsigned char> Input::downKeys;

int Input::screenCentX = 640, Input::screenCentY = 360;
int Input::lastMouseX = 640, Input::lastMouseY = 360;
int Input::mouseDeltaX = 0, Input::mouseDeltaY = 0;
int Input::mousePosX = 0, Input::mousePosY = 0;

bool Input::GetKey(unsigned char _k)
{
  for (size_t i = 0; i < keys.size(); i++)
  {
    if (keys.at(i) == _k) return true;
  }
  return false;
}
bool Input::GetKeyUp(unsigned char _k)
{
  for (size_t i = 0; i < upKeys.size(); i++)
  {
    if (upKeys.at(i) == _k) return true;
  }
  return false;
}
bool Input::GetKeyDown(unsigned char _k)
{
  for (size_t i = 0; i < downKeys.size(); i++)
  {
    if (downKeys.at(i) == _k) return true;
  }
  return false;
}

glm::vec2 Input::GetMouseDelta()
{
  float propX;
  mouseDeltaX == 0 ? propX = 0 : propX = float(mouseDeltaX / float(screenCentX));
  float propY;
  mouseDeltaY == 0 ? propY = 0 : propY = float(mouseDeltaY / float(screenCentY));

  return glm::vec2(propX, propY);
}
glm::vec2 Input::GetMouseDeltaRaw()
{
  return glm::vec2(mouseDeltaX, mouseDeltaY);
}

void Input::AddKey(unsigned char _k)
{
  //Checking for duplicates
  for (size_t i = 0; i < keys.size(); i++)
  {
    if (keys.at(i) == _k) return;
  }

  //If it didn't exist in the vector
  //must be the keydown event
  downKeys.push_back(_k);
  keys.push_back(_k);
}
void Input::RemoveKey(unsigned char _k)
{
  for (size_t i = 0; i < keys.size(); i++)
  {
    if (keys.at(i) == _k)
    {
      keys.erase(keys.begin() + i);
      //Simple push_back as multiple RemoveKey events
      //should never happen
      upKeys.push_back(_k);
      return;
    }
  }
}

void Input::UpdateMouseDelta(int _x, int _y)
{
  mouseDeltaX = lastMouseX - _x;
  mouseDeltaY = lastMouseY - _y;

  lastMouseX = _x;
  lastMouseY = _y;

  mousePosX = _x; mousePosY = _y;

  if (abs(_x - screenCentX) + abs(_y - screenCentY) >= 250)
  {
    lastMouseX = screenCentX;
    lastMouseY = screenCentY;
    Application::RecenterMouse();
  }
}