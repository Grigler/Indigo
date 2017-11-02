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
    bool Init();
    void Destroy();

  private:
    ALCdevice *device;
    ALCcontext *context;
  };
}

#endif