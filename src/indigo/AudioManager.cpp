#include "AudioManager.h"

#define NULL 0

using namespace Indigo;

bool AudioManager::Init()
{
  device = alcOpenDevice(NULL);
  if (device == NULL)
  {
    return false;
  }

  context = alcCreateContext(device, NULL);
  if (context == NULL)
  {
    return false;
  }

  if (!alcMakeContextCurrent(context))
  {
    return false;
  }
  
  return true;
}
void AudioManager::Destroy()
{
  if (!device) return;

  //destroy sources here

  //Delete buffers here

  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
}

void AudioManager::Update()
{
  for (auto i = activeSources.begin(); i < activeSources.end(); i++)
  {
    ALint state = 0;
    alGetSourcei((*i).lock()->id, AL_SOURCE_STATE, &state);
    if (state == AL_STOPPED)
    {
      alDeleteSources(1, &(*i).lock()->id);
      activeSources.erase(i);
      i--;
    }

  }
}

std::weak_ptr<Sound> AudioManager::Load(std::string _path)
{

  return std::weak_ptr<Sound>();
}


std::vector<std::shared_ptr<Sound>> sounds;

void Sound::Play()
{

}
void Sound::PlayWithVariance(float _min, float _max)
{

}