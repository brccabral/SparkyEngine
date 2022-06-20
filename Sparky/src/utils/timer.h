#pragma once

// include OS specific timing library
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
// Windows
#include <Windows.h>
#else
// Linux
#include <time.h>
#include <stdint.h>
#endif

namespace sparky
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
        void reset();
        float elapsed();
    };
} // namespace sparky
