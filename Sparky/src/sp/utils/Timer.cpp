#include "Timer.h"

#if STD_CHRONO

namespace sp
{
	Timer::Timer()
	{
		Reset();
	}

	void Timer::Reset()
	{
		m_Start = HighResolutionClock::now();
	}

	float Timer::Elapsed()
	{
		return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
	}
}

#else
namespace sp
{
	Timer::Timer()
	{
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_Frequency = 1.0 / frequency.QuadPart;
		QueryPerformanceCounter(&m_Start);
	#else
		clock_gettime(CLOCK_MONOTONIC, &m_Start);
		struct timespec now;
		clock_gettime(CLOCK_MONOTONIC, &now);
		m_Frequency = 1.0 / ((now.tv_sec + now.tv_nsec / 1000000000.0) - (m_Start.tv_sec + m_Start.tv_nsec / 1000000000.0));
		clock_gettime(CLOCK_MONOTONIC, &m_Start);
	#endif
	};

	void Timer::Reset()
	{
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		QueryPerformanceCounter(&m_Start);
	#else
		clock_gettime(CLOCK_MONOTONIC, &m_Start);
	#endif
	};
	float Timer::Elapsed()
	{

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
		return (float)(cycles * m_Frequency);
	#else
		struct timespec now;
		clock_gettime(CLOCK_MONOTONIC, &now);
		return (now.tv_sec + now.tv_nsec / 1000000000.0) - (m_Start.tv_sec + m_Start.tv_nsec / 1000000000.0);
	#endif
	};
}
#endif