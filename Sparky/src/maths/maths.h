#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

namespace sparky
{
	namespace maths
	{
		inline double toRadians(double degrees) { return degrees * (M_PI / 180.0f); };

		inline double toDegrees(double radians) { return radians * (180.0f / M_PI); }

		inline int sign(double value) { return (value > 0) - (value < 0); }
	}
}