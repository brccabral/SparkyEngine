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
            static mat4 identity();
            static mat4 orthographic(float left, float right, float bottom, float top, float near, float far); // clipping planes
            static mat4 perspective(float fov, float aspectRatio, float near, float far);                      // projection

            // operations
            static mat4 translation(const vec3& translation);
            static mat4 scale(const vec3& scale);
            static mat4 rotation(float angle, const vec3& axis);

            // operators
            mat4& multiply(const mat4& other);
            friend mat4 operator*(const mat4& left, const mat4& right);
            friend vec3 operator*(const mat4& left, const vec3& right);
            friend vec4 operator*(const mat4& left, const vec4& right);
            mat4& operator*=(const mat4& other);
        };
    } // namespace maths

} // namespace sparky
