#include "sound.h"
#include "sound_manager.h"

namespace sparky
{
	namespace audio
	{
		void setFlagAndDestroyOnFinish(ga_Handle *in_handle, void *in_context);
		void loopOnFinish(ga_Handle *in_handle, void *in_context);

		Sound::Sound(const std::string &name, const std::string &filename)
			: m_Name(name), m_Filename(filename), m_Handle(nullptr), m_Gain(1.0f), m_Position(0), m_Sound(nullptr)
		{
			std::vector<std::string> split = split_string(filename, '.');
			if (split.size() < 2)
			{
				std::cout << "[Sound] Invalid filename '" << filename << "'!" << std::endl;
				return;
			}

			m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

			if (m_Sound == nullptr)
				std::cout << "[Sound] Could not load file '" << filename << "'!" << std::endl;
		}

		Sound::~Sound()
		{
			ga_sound_release(m_Sound);
		}

		void Sound::play()
		{
			// TODO
			// creates new handles in the background, but doesn't keep track of all handles created
			// need some kind of stack to manage all handles
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, &quit, NULL);
			m_Handle->sound = this;
			m_Position = 0;
			ga_handle_seek(m_Handle, m_Position);
			ga_handle_play(m_Handle);
			setGain(m_Gain);
		};

		void Sound::loop()
		{
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &loopOnFinish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_play(m_Handle);
			setGain(m_Gain);
			m_Position = 0;
		};

		void Sound::pause()
		{
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

		};

		void Sound::stop()
		{
			if (!m_Handle)
				return;

			ga_handle_stop(m_Handle);
			//ga_handle_destroy(m_Handle);
			m_Position = 0;
		};

		gc_int32 Sound::isPlaying()
		{
			if (m_Handle)
				return ga_handle_playing(m_Handle);
			return 0;
		}

		gc_int32 Sound::isStopped()
		{
			if (m_Handle)
				return ga_handle_stopped(m_Handle);
			return 0;
		}

		void Sound::setGain(float gain)
		{
			if (gain > 1.0f)
				gain = 1.0f;

			if (gain < 0.0f)
				gain = 0.0f;

			m_Gain = gain;

			if (m_Handle)
				ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
		}

		float Sound::getGain()
		{
			if (!m_Handle)
				return m_Gain;

			ga_handle_getParamf(m_Handle, GA_HANDLE_PARAM_GAIN, &m_Gain);
			return m_Gain;
		}

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
	}
}