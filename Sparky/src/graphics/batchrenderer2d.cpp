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

    void BatchRederer2D::submit(const Renderable2D* renderable) {};
    void BatchRederer2D::flush() {};
}