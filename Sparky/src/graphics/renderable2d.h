#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "../maths/maths.h"

namespace sparky::graphics
{

    class Renderable2D
    {
    protected:
        maths::vec3 m_Position;
        maths::vec2 m_Size;
        maths::vec4 m_Color;

        VertexArray* m_VertexArray;
        IndexBuffer* m_IndexBuffer;

    protected:
        Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color);

        virtual ~Renderable2D();

        inline const maths::vec3& getPosition() const { return m_Position; }
        inline const maths::vec2& getSize() const { return m_Size; }
        inline const maths::vec4& getColor() const { return m_Color; }
    };
} // namespace sparky::graphics{}
