#include "renderable2d.h"

namespace sparky::graphics
{
    Renderable2D::Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader& shader)
        : m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
    {
        m_VertexArray = new VertexArray();
        GLfloat vertices[] = {
            0, 0, 0,
            0, size.y, 0,
            size.x, size.y, 0,
            size.x, 0, 0 };

        GLfloat colors[] = {
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w };

        m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
        m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

        GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
        m_IndexBuffer = new IndexBuffer(indices, 6);
    }

    Renderable2D::~Renderable2D()
    {
        delete m_VertexArray;
        delete m_IndexBuffer;
    }

}