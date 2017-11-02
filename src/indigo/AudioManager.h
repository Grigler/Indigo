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

#include <glm/vec3.hpp>

#include <memory>
#include <vector>
#include <string>


namespace Indigo
{
  class Sound;

  class AudioManager
  {
    friend class Engine;
    friend class Sound;
  public:
    A_API bool Init();
    A_API void Destroy();

    A_API void Update();

    static A_API std::weak_ptr<Sound> Load(std::string _path);

  private:
    ALCdevice *device;
    ALCcontext *context;

    static std::vector<std::shared_ptr<Sound>> loadedSounds;

    static std::vector<ALuint> activeSources;
  };

  class Sound
  {
    friend class AudioManager;
  public:
    //Plays without positional audio
    void A_API Play();
    //Varies pitch with a multiplyer between min and max (-1.0f, 1.0f)
    void A_API PlayWithVariance(float _min, float _max);

  private:
    std::string path;

    ALuint id;

    void LoadOGG(std::string _path,
      std::vector<char> &_bufferData, ALenum &_format, ALsizei &_freq);
  };
}

#endif