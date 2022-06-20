#include "timer.h"

namespace sparky
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

    void Timer::reset()
    {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        QueryPerformanceCounter(&m_Start);
#else
        clock_gettime(CLOCK_MONOTONIC, &m_Start);
#endif
    };
    float Timer::elapsed()
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