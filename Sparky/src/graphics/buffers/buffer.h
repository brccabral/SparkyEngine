#pragma once

#include <GL/glew.h>

namespace sparky::graphics
{
    class Buffer
    {
    private:
        GLuint m_BufferID;
        GLuint m_ComponentCount;

    public:
        Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

        void bind() const;
        void unbind() const;

        inline GLuint getComponentCount() const { return m_ComponentCount; };
    };

} // namespace sparky::graphics
