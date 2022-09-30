#include "sp/sp.h"
#include "Sound.h"
#include "SoundManager.h"

#ifdef SPARKY_PLATFORM_WEB
#include <emscripten/emscripten.h>
#else
#include <gorilla/ga.h>
#include <gorilla/gau.h>
#endif

namespace sp
{
	namespace audio
	{
		Sound::Sound(const String &name, const String &filename)
			: m_Name(name), m_Filename(filename), m_Playing(false), m_Count(0), m_Gain(1.0f), m_Handle(nullptr), m_Sound(nullptr)
		{
			std::vector<String> split = utils::SplitString(m_Filename, '.');
			if (split.size() < 2)
			{
				SP_ERROR("[Sound] Invalid file name '", m_Filename.c_str(), "'!");
				return;
			}
		#ifdef SPARKY_PLATFORM_WEB
		#else
			m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

			SP_ASSERT(m_Sound, "Failed to load sound '", m_Filename.c_str(), "'!");
		#endif
		}

		Sound::~Sound()
		{
		#ifdef SPARKY_PLATFORM_WEB
		#else
			ga_sound_release(m_Sound);
		#endif
		}

		void Sound::Play()
		{
		#ifdef SPARKY_PLATFORM_WEB
			//std::cout << "cpp play " << m_Filename << std::endl;
			SoundManagerPlay(m_Name.c_str());
		#else
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &destroy_on_finish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_play(m_Handle);
			m_Count++;
		#endif
			m_Playing = true;
			SetGain(m_Gain);
		}

		void Sound::Loop()
		{
		#ifdef SPARKY_PLATFORM_WEB
			//std::cout << "cpp loop " << m_Filename << std::endl;
			SoundManagerLoop(m_Name.c_str());
		#else
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &loop_on_finish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_play(m_Handle);
		#endif
			m_Playing = true;
			SetGain(m_Gain);
		}

		void Sound::Pause()
		{
			if (!m_Playing)
				return;

			m_Playing = false;
		#ifdef SPARKY_PLATFORM_WEB
			//std::cout << "cpp pause " << m_Filename << std::endl;
			SoundManagerPause(m_Name.c_str());
		#else
			ga_handle_stop(m_Handle);
		#endif
		}

		void Sound::Stop()
		{
			if (!m_Playing)
				return;

		#ifdef SPARKY_PLATFORM_WEB
			//std::cout << "cpp stop " << m_Filename << std::endl;
			SoundManagerStop(m_Name.c_str());
		#else
			ga_handle_stop(m_Handle);
		#endif
			m_Playing = false;
		}

		void Sound::SetGain(float gain)
		{
			if (gain > 1.0f)
				gain = 1.0f;

			if (gain < 0.0f)
				gain = 0.0f;

			m_Gain = gain;

			if (!m_Playing)
			{
				SP_WARN("[Sound] Cannot set gain! Sound is not currently playing!");
				return;
			}
		#ifdef SPARKY_PLATFORM_WEB
			//std::cout << "cpp gain " << m_Filename << std::endl;
			SoundManagerSetGain(m_Name.c_str(), gain);
		#else
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, m_Gain);
		#endif
		}

		void Sound::Resume()
		{
			if (m_Playing)
				return;

			m_Playing = true;
		#ifdef SPARKY_PLATFORM_WEB
			//std::cout << "cpp resume " << m_Filename << std::endl;
			SoundManagerPlay(m_Name.c_str());
		#else
			ga_handle_play(m_Handle);
		#endif
			SetGain(m_Gain);
		}

	#ifdef SPARKY_PLATFORM_WEB
	#else
		void destroy_on_finish(ga_Handle *in_handle, void *in_context)
		{
			Sound *sound = (Sound *)in_handle->sound;
			sound->m_Count--;
			if (sound->m_Count == 0)
				sound->Stop();
		}

		void loop_on_finish(ga_Handle *in_handle, void *in_context)
		{
			ga_handle_destroy(in_handle);
			Sound *sound = (Sound *)in_handle->sound;
			sound->Loop();
		}
	#endif

	}
}