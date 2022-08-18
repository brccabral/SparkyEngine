#pragma once

#include <string>
#include <iostream>
#include "gorilla/ga.h"
#include "gorilla/gau.h"

namespace sparky::audio
{
	class Sound
	{
	private:
		std::string m_Name;
		std::string m_Filename;
		ga_Sound *m_Sound;
		ga_Handle *m_Handle;

		float m_Gain;

	public:
		Sound(const std::string &name, const std::string &filename);
		~Sound();

		void play();
		void loop();
		void pause();
		void stop();

		void setGain(float gain);
		float getGain();

		inline const std::string &getName() const { return m_Name; }
		inline const std::string &getFilename() const { return m_Filename; }
		gc_int32 isPlaying();

		friend void setFlagAndDestroyOnFinish(ga_Handle *in_handle, void *in_context);
		friend void loopOnFinish(ga_Handle *in_handle, void *in_context);
	};
}