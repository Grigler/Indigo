#ifndef __IND_INPUT__
#define __IND_INPUT__

#include <vector>

#include <glm/vec2.hpp>

namespace Indigo
{
  class Input
  {
    friend class Application;
  public:
    //TODO - replace unsigned char with some enum wrapper for keys
    static bool GetKey(unsigned char _k);
    static bool GetKeyUp(unsigned char _k);
    static bool GetKeyDown(unsigned char _k);

    //Returns mouse movement in proportion to the screen size
    static glm::vec2 GetMouseDelta();
    static glm::vec2 GetMouseDeltaRaw();
    static glm::vec2 GetMousePos() { return glm::vec2(mousePosX, mousePosY); }

  private:
    static void AddKey(unsigned char _k);
    static void RemoveKey(unsigned char _k);

    //Vector to avoid memory allocation needs of a list
    static std::vector<unsigned char> keys;
    static std::vector<unsigned char> upKeys;
    static std::vector<unsigned char> downKeys;

    static int lastMouseX, lastMouseY;
    static int screenCentX, screenCentY;
    static void UpdateMouseDelta(int _x, int _y);

    static int mouseDeltaX, mouseDeltaY;
    static int mousePosX, mousePosY;

  };
}

#endif