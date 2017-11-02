#include "AudioManager.h"

#include "Application.h"

using namespace Indigo;

bool AudioManager::Init()
{
  device = alcOpenDevice(NULL);
  if (device == NULL)
  {
    Application::ErrPrint("Failed to open audio device");
    return false;
  }

  context = alcCreateContext(device, NULL);
  if (context == NULL)
  {
    Application::ErrPrint("Failed to create audio context");
    return false;
  }

  if (!alcMakeContextCurrent(context))
  {
    Application::ErrPrint("Failed to make context current");
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