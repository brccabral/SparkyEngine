#pragma once

#include "sp/Common.h"
#include <string>
#include <vector>
#include "Sound.h"

#ifdef SPARKY_PLATFORM_WEB
extern "C" void SoundManagerAdd(const char *name, const char *filename);
extern "C" void SoundManagerPlay(const char *name);
extern "C" void SoundManagerPause(const char *name);
extern "C" void SoundManagerStop(const char *name);
extern "C" void SoundManagerLoop(const char *name);
extern "C" void SoundManagerSetGain(const char *name, double gain);
#endif

#ifndef SP_PLATFORM_WEB
struct gau_Manager;
struct ga_Mixer;
#endif

namespace sp
{
	namespace audio
	{
		class SP_API SoundManager
		{
			friend class Sound; // Sound can access private members
		private:
			static std::vector<Sound *> m_Sounds;
			SoundManager() {};
			
		#ifdef SPARKY_PLATFORM_WEB
		#else
			static gau_Manager *m_Manager;
			static ga_Mixer *m_Mixer;
		#endif

		public:
			static void Init();
			static Sound *Add(Sound *sound);
			static Sound *Get(const String &name);
			static void Update();
			static void Clean();
		};
	}
}