#ifndef __IND_AUDIO_MANAGER__
#define __IND_AUDIO_MANAGER__

//Defined in config - used to switch between
//dllimport (for engine) and dllexport (for dll build)
#ifndef IND_AUDIO_OPENAL
#define A_API __declspec(dllexport)
#else
#define A_API __declspec(dllimport)
#endif

#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <vector>
#include <string>

namespace Indigo
{
  class Sound;

  class AudioManager
  {
    friend class Engine;
  public:
    A_API bool Init();
    A_API void Destroy();

    A_API void Update();

    static A_API std::weak_ptr<Sound> Load(std::string _path);

  private:
    ALCdevice *device;
    ALCcontext *context;

    static std::vector<std::shared_ptr<Sound>> loadedSounds;

    std::vector<std::weak_ptr<Sound>> activeSources;
  };

  class Sound
  {
    friend class AudioManager;
  public:
    void Play();
    //Varies pitch with a multiplyer between min and max
    void PlayWithVariance(float _min, float _max);
    
  private:
    std::string path;

    ALuint id;

  };
}

#endif