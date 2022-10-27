#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "sp/Common.h"

namespace sp
{
	namespace maths
	{

		SP_API inline float toRadians(float degrees)
		{
			return (float)(degrees * (M_PI / 180.0));
		}

		SP_API inline float toDegrees(float radians)
		{
			return (float)(radians * (180.0f / M_PI));
		}

		SP_API inline int sign(float value)
		{
			return (value > 0) - (value < 0);
		}

		SP_API inline float sin(float angle)
		{
			return (float)::sin(angle);
		}

		SP_API inline float cos(float angle)
		{
			return (float)::cos(angle);
		}

		SP_API inline float tan(float angle)
		{
			return (float)::tan(angle);
		}

		SP_API inline float sqrt(float value)
		{
			return (float)::sqrt(value);
		}

		SP_API inline float rsqrt(float value)
		{
			return 1.0f / (float)::sqrt(value);
		}

		SP_API inline float asin(float value)
		{
			return (float)::asin(value);
		}

		SP_API inline float acos(float value)
		{
			return (float)::acos(value);
		}

		SP_API inline float atan(float value)
		{
			return (float)::atan(value);
		}

		SP_API inline float atan2(float y, float x)
		{
			return (float)::atan2(y, x);
		}

		SP_API inline float min(float value, float minimum)
		{
			return (value < minimum) ? minimum : value;
		}

		SP_API inline float max(float value, float maximum)
		{
			return (value > maximum) ? maximum : value;
		}

		SP_API inline float clamp(float value, float minimum, float maximum)
		{
			return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
		}

	}
}