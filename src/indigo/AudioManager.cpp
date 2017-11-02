#include "AudioManager.h"

//OGG Loading
#include <vorbis/vorbisfile.h>

#include <iostream>

#define NULL 0

using namespace Indigo;

std::vector<std::shared_ptr<Sound>> AudioManager::loadedSounds;
std::vector<ALuint> AudioManager::activeSources;

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
  //Iterating through activeSources and removing those that have finished
  for (auto i = activeSources.begin(); i < activeSources.end(); i++)
  {
    ALint state = 0;
    alGetSourcei((*i), AL_SOURCE_STATE, &state);
    if (state == AL_STOPPED)
    {
      alDeleteSources(1, &(*i));
      activeSources.erase(i);
      i--;
    }
  }
}

std::weak_ptr<Sound> AudioManager::Load(std::string _path)
{
  for (auto i = loadedSounds.begin(); i < loadedSounds.end(); i++)
  {
    if ((*i)->path == _path)
    {
      return std::weak_ptr<Sound>((*i));
    }
  }

  std::shared_ptr<Sound> rtn = std::make_shared<Sound>();
  
  ALenum format = 0;
  ALsizei freq = 0;
  std::vector<char> bufferData;

  alGenBuffers(1, &rtn->id);

  rtn->path = _path;
  rtn->LoadOGG(_path, bufferData, format, freq);

  alBufferData(rtn->id, format, &bufferData[0],
    static_cast<ALsizei>(bufferData.size()), freq);

  AudioManager::loadedSounds.push_back(rtn);

  return std::weak_ptr<Sound>(rtn);
}

void Sound::Play()
{
  ALuint sourceId = 0;
  alGenSources(1, &sourceId);
  alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
  alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
  alSourcei(sourceId, AL_BUFFER, id);
  alSourcePlay(sourceId);

  AudioManager::activeSources.push_back(sourceId);
}
void Sound::PlayWithVariance(float _min, float _max)
{
  //For rand resolution
  _min *= 1000.0f; _max *= 1000.0f;
  float variance = (rand() % ((int)_min + 1 - (int)_max) + (int)_min) / 1000.0f;

  ALuint sourceId = 0;
  alGenSources(1, &sourceId);
  alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
  alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
  alSourcei(sourceId, AL_BUFFER, id);
  alSourcef(sourceId, AL_PITCH, variance);
  alSourcePlay(sourceId);
}

void Sound::LoadOGG(std::string _path,
  std::vector<char> &_bufferData, ALenum &_format, ALsizei &_freq)
{
  int endian = 0;
  int bitStream = 0;
  long bytes = 0;
  char array[2048] = { 0 };
  vorbis_info *pInfo = NULL;
  OggVorbis_File oggFile = { 0 };

  // Use the inbuilt fopen to create a file descriptor
  if (ov_fopen(_path.c_str(), &oggFile) != 0)
  {
    throw std::exception();
  }

  // Extract information from the file header
  pInfo = ov_info(&oggFile, -1);

  // Record the format required by OpenAL
  if (pInfo->channels == 1)
  {
    _format = AL_FORMAT_MONO16;
  }
  else
  {
    _format = AL_FORMAT_STEREO16;
  }

  // Record the sample rate required by OpenAL
  _freq = pInfo->rate;

  // Keep reading bytes from the file to populate the output buffer
  while (true)
  {
    // Read bytes into temporary array
    bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitStream);

    if (bytes < 0)
    {
      ov_clear(&oggFile);
      std::cout << "Failed to decode file '" << _path << "'." << std::endl;
      throw std::exception();
    }
    else if (bytes == 0)
    {
      break;
    }

    // Copy from temporary array into output buffer
    _bufferData.insert(_bufferData.end(), array, array + bytes);
  }

  // Clean up and close the file
  ov_clear(&oggFile);
}