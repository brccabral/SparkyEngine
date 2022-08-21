#include "sound.h"
#include "sound_manager.h"

namespace sparky
{
	namespace audio
	{
	#ifdef SPARKY_EMSCRIPTEN
	#else
		void setFlagAndDestroyOnFinish(ga_Handle *in_handle, void *in_context);
		void loopOnFinish(ga_Handle *in_handle, void *in_context);
	#endif

		Sound::Sound(const std::string &name, const std::string &filename)
		#ifdef SPARKY_EMSCRIPTEN
			: m_Name(name), m_Filename(filename), m_Gain(1.0f), m_Position(0)
		#else
			: m_Name(name), m_Filename(filename), m_Handle(nullptr), m_Gain(1.0f), m_Position(0), m_Sound(nullptr)
		#endif
		{
			std::vector<std::string> split = split_string(filename, '.');
			if (split.size() < 2)
			{
				std::cout << "[Sound] Invalid filename '" << filename << "'!" << std::endl;
				return;
			}
		#ifdef SPARKY_EMSCRIPTEN
		#else
			m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

			if (m_Sound == nullptr)
				std::cout << "[Sound] Could not load file '" << filename << "'!" << std::endl;
		#endif
		}

		Sound::~Sound()
		{
		#ifdef SPARKY_EMSCRIPTEN
		#else
			ga_sound_release(m_Sound);
		#endif
		}

		void Sound::play()
		{
			m_Position = 0;
		#ifdef SPARKY_EMSCRIPTEN
		#else
			// TODO
			// creates new handles in the background, but doesn't keep track of all handles created
			// need some kind of stack to manage all handles
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_seek(m_Handle, m_Position);
			ga_handle_play(m_Handle);
			setGain(m_Gain);
		#endif
		};

		void Sound::loop()
		{
			m_Position = 0;
		#ifdef SPARKY_EMSCRIPTEN
		#else
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &loopOnFinish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_play(m_Handle);
		#endif
			setGain(m_Gain);
		};

		void Sound::pause()
		{
		#ifdef SPARKY_EMSCRIPTEN
		#else
			if (!m_Handle)
			{
				std::cout << m_Name << ": No sound to pause/resume." << std::endl;
				return;
			}

			if (isPlaying())
			{
				m_Position = ga_handle_tell(m_Handle, GA_TELL_PARAM_CURRENT);
				ga_handle_stop(m_Handle);
			}
			else if (m_Position)
			{
				ga_handle_seek(m_Handle, m_Position);
				ga_handle_play(m_Handle);
				setGain(m_Gain);
			}
			else
			{
				std::cout << m_Name << " is stopped, cannot resume." << std::endl;
			}
		#endif

		};

		void Sound::stop()
		{
		#ifdef SPARKY_EMSCRIPTEN
		#else
			if (!m_Handle)
				return;

			ga_handle_stop(m_Handle);
			//ga_handle_destroy(m_Handle);
		#endif
			m_Position = 0;
		};

		int Sound::isPlaying()
		{
		#ifdef SPARKY_EMSCRIPTEN
		#else
			if (m_Handle)
				return ga_handle_playing(m_Handle);
		#endif
			return 0;
		}

		int Sound::isStopped()
		{
		#ifdef SPARKY_EMSCRIPTEN
		#else
			if (m_Handle)
				return ga_handle_stopped(m_Handle);
		#endif
			return 0;
		}

		void Sound::setGain(float gain)
		{
			if (gain > 1.0f)
				gain = 1.0f;

			if (gain < 0.0f)
				gain = 0.0f;

			m_Gain = gain;

		#ifdef SPARKY_EMSCRIPTEN
		#else
			if (m_Handle)
				ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
		#endif
		}

		float Sound::getGain()
		{
		#ifdef SPARKY_EMSCRIPTEN
		#else
			if (!m_Handle)
				return m_Gain;

			ga_handle_getParamf(m_Handle, GA_HANDLE_PARAM_GAIN, &m_Gain);
		#endif
			return m_Gain;
		}

	#ifdef SPARKY_EMSCRIPTEN
	#else
		void setFlagAndDestroyOnFinish(ga_Handle *in_handle, void *in_context)
		{
			gc_int32 *flag = (gc_int32 *)(in_context);
			*flag = 1;
			ga_handle_destroy(in_handle);
			Sound *sound = (Sound *)in_handle->sound;
			sound->m_Position = 0;
		}

		void loopOnFinish(ga_Handle *in_handle, void *in_context)
		{
			ga_handle_destroy(in_handle);
			Sound *sound = (Sound *)in_handle->sound;
			sound->loop();
			sound->m_Position = 0;
		}
	#endif
	}
}