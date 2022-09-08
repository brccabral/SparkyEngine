#pragma once

#include "vec3.h"
#include "vec4.h"

namespace sparky
{
	namespace maths
	{
		struct mat4
		{
			// both "float elements" and "vec4 columns" represent the same memory address
			union
			{
				float elements[16]; // 4*4
				vec4 columns[4];
			};

			mat4();
			mat4(float diagonal);

			// creators
			mat4 &Invert();
			static mat4 Identity();
			static mat4 Orthographic(float left, float right, float bottom, float top, float near, float far); // clipping planes
			static mat4 Perspective(float fov, float aspectRatio, float near, float far);                      // projection

			// operations
			static mat4 Translate(const vec3 &translation);
			static mat4 Scale(const vec3 &scale);
			static mat4 Rotate(float angle, const vec3 &axis);
			static mat4 Invert(const mat4 &matrix);

			// operators
			mat4 &Multiply(const mat4 &other);
			friend mat4 operator*(const mat4 &left, const mat4 &right);
			friend vec3 operator*(const mat4 &left, const vec3 &right);
			friend vec4 operator*(const mat4 &left, const vec4 &right);
			mat4 &operator*=(const mat4 &other);
		};
	} // namespace maths

} // namespace sparky
