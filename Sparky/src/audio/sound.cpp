#include "sound.h"
#include "sound_manager.h"

namespace sparky::audio
{
	void setFlagAndDestroyOnFinish(ga_Handle *in_handle, void *in_context);
	void loopOnFinish(ga_Handle *in_handle, void *in_context);

	Sound::Sound(const std::string &name, const std::string &filename)
		: m_Name(name), m_Filename(filename), m_Handle(nullptr)
	{
		m_Sound = gau_load_sound_file(filename.c_str(), "wav");
	}

	Sound::~Sound()
	{
		ga_sound_release(m_Sound);
	}

	void Sound::play()
	{
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, &quit, NULL);
		m_Handle->sound = this;
		ga_handle_play(m_Handle);
	};

	void Sound::loop()
	{

	};

	void Sound::pause()
	{

	};

	void Sound::stop()
	{

	};

	void setFlagAndDestroyOnFinish(ga_Handle *in_handle, void *in_context)
	{
		gc_int32 *flag = (gc_int32 *)(in_context);
		*flag = 1;
		ga_handle_destroy(in_handle);
	}

	void loopOnFinish(ga_Handle *in_handle, void *in_context)
	{
		Sound *sound = (Sound *)in_handle->sound;
		sound->loop();
		ga_handle_destroy(in_handle);
	}
}