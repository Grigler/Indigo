#ifndef __IND_AUDIO_MANAGER__
#define __IND_AUDIO_MANAGER

//#include "../example/config.h"

#ifdef IND_AUDIO_OPENAL
  #include "AL_AUDIO/AudioManager.h"
#else
  //Some other audio lib with relevant functionality
#endif

#endif