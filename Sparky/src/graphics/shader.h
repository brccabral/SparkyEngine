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

        void setUniformMat4(const GLchar* name, const maths::mat4& matrix);
        void setUniform1i(const GLchar* name, int value);
        void setUniform1f(const GLchar* name, float value);
        void setUniform2f(const GLchar* name, const maths::vec2& vector);
        void setUniform3f(const GLchar* name, const maths::vec3& vector);
        void setUniform4f(const GLchar* name, const maths::vec4& vector);

    private:
        GLuint load();

        GLint getUniformLocation(const GLchar* name);
    };
} // namespace sparky::graphics
