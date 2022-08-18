#pragma once

#include <string>
#include <vector>
#include "sound.h"

namespace sparky::audio
{
	class SoundManager
	{
		friend class Sound; // Sound can access private members
	private:
		static std::vector<Sound *> m_Sounds;
		static gau_Manager *m_Manager;
		static ga_Mixer *m_Mixer;
		SoundManager() {};
	public:
		static void init();
		static void add(Sound *sound);
		static Sound *get(const std::string &name);
		static void update();
		static void clean();
	};
}