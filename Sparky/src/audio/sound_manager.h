#pragma once

#include <string>
#include <vector>
#include "sound.h"

namespace sparky
{
	namespace audio
	{
		class SoundManager
		{
			friend class Sound; // Sound can access private members
		private:
			static std::vector<Sound *> m_Sounds;
			SoundManager() {};
		#ifdef SPARKY_EMSCRIPTEN
		#else
			static gau_Manager *m_Manager;
			static ga_Mixer *m_Mixer;
		#endif
		public:
			static void init();
			static void add(Sound *sound);
			static Sound *get(const std::string &name);
			static void update();
			static void clean();
		};
	}
}