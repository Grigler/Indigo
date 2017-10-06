#ifndef __IND_INPUT__
#define __IND_INPUT__

#include <vector>

namespace Indigo
{
  class Input
  {
    friend class Application;
  public:
    //TODO - replace unsigned char with some enum wrapper for keys
    static bool GetKey(unsigned char _k);
    static bool GetKeyUp(unsigned char _k);

  private:
    static void AddKey(unsigned char _k);
    static void RemoveKey(unsigned char _k);

    //Vector to avoid memory allocation needs
    static std::vector<unsigned char> keys;
    static std::vector<unsigned char> upKeys;
  };
}

#endif