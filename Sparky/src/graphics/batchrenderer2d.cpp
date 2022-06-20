#include "batchrenderer2d.h"

namespace sparky::graphics
{
    BatchRederer2D::BatchRederer2D()
    {
        init();
    };
    BatchRederer2D::~BatchRederer2D()
    {
        delete m_IBO;
        glDeleteBuffers(1, &m_VBO);
    }

    void BatchRederer2D::init()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

        // get the vertex position based on VertexData
        glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
        glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);

        // get the color position based on VertexData
        glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(SHADER_COLOR_INDEX);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // bind and unbind costs a lot

        // create triangle indices
        // t1 = 0,1,2, 2,3,0
        // t2 = 4,5,6, 6,7,4
        GLushort indices[RENDERER_INDICES_SIZE];
        int offset = 0;
        for (int i = 0; i < RENDERER_INDICES_SIZE - 6; i += 6)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
        glBindVertexArray(0);
    };

    void BatchRederer2D::begin()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    };

    // submit will create a rectangle
    void BatchRederer2D::submit(const Renderable2D* renderable)
    {
        // indices 0,1,2, 2,3,0
        const maths::vec3& position = renderable->getPosition();
        const maths::vec2& size = renderable->getSize();
        const maths::vec4& color = renderable->getColor();

        m_Buffer->vertex = position;
        m_Buffer->color = color;
        m_Buffer++;

        m_Buffer->vertex = maths::vec3(position.x, position.y + size.y, position.z);
        m_Buffer->color = color;
        m_Buffer++;

        m_Buffer->vertex = maths::vec3(position.x + size.x, position.y + size.y, position.z);
        m_Buffer->color = color;
        m_Buffer++;

        m_Buffer->vertex = maths::vec3(position.x + size.x, position.y, position.z);
        m_Buffer->color = color;
        m_Buffer++;

        m_IndexCount += 6;
    };
    void BatchRederer2D::end()
    {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    };

    void BatchRederer2D::flush()
    {
        glBindVertexArray(m_VAO);
        m_IBO->bind();

        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, NULL);

        m_IBO->unbind();
        glBindVertexArray(0);
        m_IndexCount = 0;
    }
}