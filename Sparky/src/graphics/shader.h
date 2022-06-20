#pragma once

#include <GL/glew.h>
#include "../utils/fileutils.h"
#include "../maths/maths.h"

namespace sparky::graphics
{
    class Shader
    {
    private:
        GLuint m_ShaderID; // shader ID given by openGl
        const char* m_vertPath;
        const char* m_fragPath;

    public:
        Shader(const char* vertPath, const char* fragPath);
        ~Shader();

        void enable() const;
        void disable() const;

        void setUniform(const GLchar* name, const maths::mat4& matrix) const;
        void setUniform(const GLchar* name, int value);
        void setUniform(const GLchar* name, float value);
        void setUniform(const GLchar* name, const maths::vec2& vector);
        void setUniform(const GLchar* name, const maths::vec3& vector);
        void setUniform(const GLchar* name, const maths::vec4& vector);

    private:
        GLuint load();

        GLint getUniformLocation(const GLchar* name) const;
    };
} // namespace sparky::graphics
