#pragma once

#include <string>
#include <utils/Log.h>
#include "../utils/stringutils.h"
#include <sparky_types.h>

#ifdef SPARKY_PLATFORM_WEB
#include <emscripten/emscripten.h>
#else
#include "gorilla/ga.h"
#include "gorilla/gau.h"
#endif

namespace sparky
{
	namespace audio
	{
		class Sound
		{
		private:
			std::string m_Name;
			std::string m_Filename;
			uint m_Count;
		#ifdef SPARKY_PLATFORM_WEB
		#else
			ga_Sound *m_Sound;
			ga_Handle *m_Handle;
		#endif

			float m_Gain;
			bool m_Playing;

		public:
			Sound(const std::string &name, const std::string &filename);
			~Sound();

			void play();
			void loop();
			void pause();
			void resume();
			void stop();

			void setGain(float gain);
			float getGain();

			inline const bool isPlaying() const { return m_Playing; }
			inline const float getGain() const { return m_Gain; }
			inline const std::string &getName() const { return m_Name; }
			inline const std::string &getFilename() const { return m_Filename; }

		#ifdef SPARKY_PLATFORM_WEB
		#else
			friend void destroy_on_finish(ga_Handle *in_handle, void *in_context);
			friend void loop_on_finish(ga_Handle *in_handle, void *in_context);
		#endif

		};

	}
}