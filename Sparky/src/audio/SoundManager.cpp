#include "SoundManager.h"


namespace sparky
{
	namespace audio
	{
	#ifndef SPARKY_PLATFORM_WEB
		gau_Manager *SoundManager::m_Manager = nullptr;
		ga_Mixer *SoundManager::m_Mixer = nullptr;
	#endif

		std::vector<Sound *> SoundManager::m_Sounds;

		Sound *SoundManager::add(Sound *sound)
		{
			m_Sounds.push_back(sound);
		#ifdef SPARKY_PLATFORM_WEB
			//std::cout << "cpp add name " << sound->getName() << " filename " << sound->getFilename() << std::endl;
			SoundManagerAdd(sound->getName().c_str(), sound->getFilename().c_str());
		#endif
			return sound;
		}

		Sound *SoundManager::get(const std::string &name)
		{
			for (Sound *sound : m_Sounds)
			{
				if (sound->getName() == name)
					return sound;
			}
			return nullptr;
		}

		void SoundManager::update()
		{
		#ifdef SPARKY_PLATFORM_WEB
		#else
			gau_manager_update(SoundManager::m_Manager);
		#endif
		}

		void SoundManager::clean()
		{
			for (uint i = 0; i < m_Sounds.size(); i++)
				delete m_Sounds[i];

		#ifdef SPARKY_PLATFORM_WEB
		#else
			gau_manager_destroy(m_Manager);
			gc_shutdown();
		#endif
		}

		void SoundManager::init()
		{
		#ifdef SPARKY_PLATFORM_WEB
			EM_ASM({
				Module.SoundManager = { };
			Module.SoundManager.m_Sounds = { };
			Module.SoundManagerAdd = function(name, filename)
			{
				//console.log('module add ' + name + ' filename ' + filename); 
				Module.SoundManager.m_Sounds[name] = new Audio(filename);
			};
			Module.SoundManagerPlay = function(name) { Module.SoundManager.m_Sounds[name].play(); };
			Module.SoundManagerPause = function(name) { Module.SoundManager.m_Sounds[name].pause(); };
			Module.SoundManagerStop = function(name) { Module.SoundManagerPause(name); Module.SoundManager.m_Sounds[name].currentTime = 0; Module.SoundManager.m_Sounds[name].loop = false; };
			Module.SoundManagerLoop = function(name) { Module.SoundManager.m_Sounds[name].play(); Module.SoundManager.m_Sounds[name].loop = true; };
			Module.SoundManagerSetGain = function(name, gain) { Module.SoundManager.m_Sounds[name].volume = gain; };
				}
			);
		#else
			gc_initialize(0);
			m_Manager = gau_manager_create();
			m_Mixer = gau_manager_mixer(m_Manager);
		#endif
		}
	}
}