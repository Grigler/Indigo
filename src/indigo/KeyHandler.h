#ifndef __IND_KEY_HANDLER__
#define __IND_KEY_HANDLER__

#include <list>

namespace Indigo
{
  class KeyHandler
  {
    friend class Environment;
  public:

    static bool GetKey(unsigned char _key);
    static void StartUp();
    static void PollCurrWindow();

  private:
    //Private constructor with env friend class
    //so only env can have the KeyHandler singleton
    KeyHandler();

    static KeyHandler *instance;

    static void KeyReg(unsigned char _key, int _mX, int _mY);
    static void KeyUpReg(unsigned char _key, int _mX, int _mY);

    std::list<unsigned char> keys;
  };

} //End of namespace

#endif