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