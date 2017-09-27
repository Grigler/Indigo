#include "KeyHandler.h"

#include <GL/freeglut.h>

#include <iostream>

using namespace Indigo;

KeyHandler* KeyHandler::instance = nullptr;

KeyHandler::KeyHandler()
{
  if (instance != nullptr)
  {
    throw std::exception();
  }
  instance = this;
}
void KeyHandler::StartUp()
{
  if (instance != nullptr)
  {
    glutKeyboardFunc(instance->KeyReg);
    glutKeyboardUpFunc(instance->KeyUpReg);
  }
}
void KeyHandler::PollCurrWindow()
{
  //Just need to re-register the keyboard for a new window
  StartUp();
}

bool KeyHandler::GetKey(unsigned char _key)
{
  for (std::list<unsigned char>::iterator i = instance->keys.begin();
    i != instance->keys.end(); i++)
  {
    if ((*i) == _key) return true;
  }
  return false;
}

void KeyHandler::KeyReg(unsigned char _key, int _mX, int _mY)
{
  std::cout << "Down:\t" << _key << std::endl;
  //Checking if it already exists in the list
  for (std::list<unsigned char>::iterator i = instance->keys.begin();
    i != instance->keys.end(); i++)
  {
    if ((*i) == _key)
    {
      std::cout << "Already Exists \n";
      return;
    }
  }
  instance->keys.push_back(_key);
}
void KeyHandler::KeyUpReg(unsigned char _key, int _mX, int _mY)
{
  std::cout << "Up:\t" << _key << std::endl;
  for (std::list<unsigned char>::iterator i = instance->keys.begin();
    i != instance->keys.end(); i++)
  {
    if ((*i) == _key)
    {
      instance->keys.erase(i);
      return;
    }
  }
}