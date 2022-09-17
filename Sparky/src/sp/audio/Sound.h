#pragma once

#include <string>
#include <sp/utils/Log.h>
#include <sp/utils/StringUtils.h>
#include <sp/Types.h>

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
		class Sound
		{
		private:
			String m_Name;
			String m_Filename;
			uint m_Count;
		#ifdef SPARKY_PLATFORM_WEB
		#else
			ga_Sound *m_Sound;
			ga_Handle *m_Handle;
		#endif

			float m_Gain;
			bool m_Playing;

		public:
			Sound(const String &name, const String &filename);
			~Sound();

			void Play();
			void Loop();
			void Pause();
			void Resume();
			void Stop();

			void SetGain(float gain);

			inline const bool IsPlaying() const { return m_Playing; }
			inline const float GetGain() const { return m_Gain; }
			inline const String &GetName() const { return m_Name; }
			inline const String &GetFilename() const { return m_Filename; }

		#ifdef SPARKY_PLATFORM_WEB
		#else
			friend void destroy_on_finish(ga_Handle *in_handle, void *in_context);
			friend void loop_on_finish(ga_Handle *in_handle, void *in_context);
		#endif

		};

	}
}