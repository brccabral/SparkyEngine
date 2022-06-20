#pragma once

#include <GL/glew.h>

namespace sparky::graphics
{
    class IndexBuffer
    {
    private:
        GLuint m_BufferID;
        GLsizei m_Count;

    public:
        IndexBuffer(GLushort* data, GLsizei count);
        IndexBuffer(GLuint* data, GLsizei count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        inline GLsizei getCount() const { return m_Count; };
    };

} // namespace sparky::graphics
