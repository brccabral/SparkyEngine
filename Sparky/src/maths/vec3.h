#pragma once

#include <iostream>
#include <sparky_types.h>

namespace sparky
{
	namespace maths
	{
		struct vec2;

		struct vec3
		{
			float x, y, z;

			vec3();
			vec3(float x, float y, float z);
			vec3(int x, int y, int z);
			vec3(const vec2 &other);

			vec3 &add(const vec3 &other);
			vec3 &subtract(const vec3 &other);
			vec3 &multiply(const vec3 &other);
			vec3 &divide(const vec3 &other);

			friend std::ostream &operator<<(std::ostream &stream, const vec3 &vector);

			friend vec3 operator+(const vec3 &left, const vec3 &right);
			friend vec3 operator-(const vec3 &left, const vec3 &right);
			friend vec3 operator*(const vec3 &left, const vec3 &right);
			friend vec3 operator/(const vec3 &left, const vec3 &right);

			vec3 &operator+=(const vec3 &other);
			vec3 &operator-=(const vec3 &other);
			vec3 &operator*=(const vec3 &other);
			vec3 &operator/=(const vec3 &other);

			bool operator==(const vec3 &other);
			bool operator!=(const vec3 &other);

			float distance(const vec3 &other) const;
		};

	} // namespace maths

} // namespace math
