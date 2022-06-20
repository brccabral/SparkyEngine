#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "../maths/maths.h"
#include "shader.h"

namespace sparky::graphics
{
    struct VertexData
    {
        maths::vec3 vertex;
        maths::vec4 color;
    };

    class Renderable2D
    {
    protected:
        maths::vec3 m_Position;
        maths::vec2 m_Size;
        maths::vec4 m_Color;

        VertexArray* m_VertexArray;
        IndexBuffer* m_IndexBuffer;
        Shader& m_Shader;

    public:
        Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader& shader);

        virtual ~Renderable2D();

    public:
        inline const VertexArray* getVAO() const { return m_VertexArray; };
        inline const IndexBuffer* getIBO() const { return m_IndexBuffer; };
        inline const Shader& getShader() const { return m_Shader; };
        inline const maths::vec3& getPosition() const { return m_Position; }
        inline const maths::vec2& getSize() const { return m_Size; }
        inline const maths::vec4& getColor() const { return m_Color; }
    };
} // namespace sparky::graphics{}
