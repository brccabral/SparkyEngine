#pragma once

#include "sp/Common.h"

#define STD_CHRONO 1

#if STD_CHRONO

#include <chrono>

namespace sp
{
	class SP_API Timer
	{
	private:
		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<HighResolutionClock> m_Start;
	public:
		Timer();

		void Reset();

		float Elapsed();

	};
}

#else

// include OS specific timing library
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
// Windows
#include <Windows.h>
#else
// Linux
#include <time.h>
#include <stdint.h>
#endif

namespace sp
{
	class Timer
	{
	private:
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		LARGE_INTEGER m_Start;
	#else
		struct timespec m_Start;
	#endif
		double m_Frequency;

	public:
		Timer();
		void Reset();
		float Elapsed();
	};
} // namespace sp

#endif