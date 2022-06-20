#pragma once

#include <GL/glew.h>
#include "../utils/fileutils.h"

namespace sparky::graphics
{
    class Shader
    {
    public:
        GLuint m_ShaderID; // shader ID given by openGl
        const char* m_vertPath;
        const char* m_fragPath;

    public:
        Shader(const char* vertPath, const char* fragPath);
        ~Shader();

        void enable() const;
        void disable() const;

    private:
        GLuint load();
    };
} // namespace sparky::graphics
