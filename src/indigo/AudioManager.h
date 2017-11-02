#ifndef IND_AUDIO_OPENAL
#define A_API __declspec(dllexport)
#else
#define A_API __declspec(dllimport)
#endif

#ifndef __IND_AUDIO_MANAGER__
#define __IND_AUDIO_MANAGER__

#include <AL/al.h>
#include <AL/alc.h>

namespace Indigo
{
  class AudioManager
  {
    friend class Engine;
  public:
    A_API bool Init();
    A_API void Destroy();

  private:
    ALCdevice *device;
    ALCcontext *context;

  };
}

#endif