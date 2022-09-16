#pragma once

#include <string>
#include <sp/utils/Log.h>
#include "../utils/StringUtils.h"
#include <sp/sparky_types.h>

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

			void Play();
			void Loop();
			void Pause();
			void Resume();
			void Stop();

			void SetGain(float gain);

			inline const bool IsPlaying() const { return m_Playing; }
			inline const float GetGain() const { return m_Gain; }
			inline const std::string &GetName() const { return m_Name; }
			inline const std::string &GetFilename() const { return m_Filename; }

		#ifdef SPARKY_PLATFORM_WEB
		#else
			friend void destroy_on_finish(ga_Handle *in_handle, void *in_context);
			friend void loop_on_finish(ga_Handle *in_handle, void *in_context);
		#endif

		};

	}
}