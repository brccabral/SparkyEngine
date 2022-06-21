#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "../maths/maths.h"
#include "shader.h"
#include "renderer2d.h"

namespace sparky::graphics
{
    struct VertexData
    {
        maths::vec3 vertex;
        // maths::vec4 color;
        unsigned int color;
    };

    class Renderable2D
    {
    protected:
        maths::vec3 m_Position;
        maths::vec2 m_Size;
        maths::vec4 m_Color;

        Renderable2D() = default;

    public:
        Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color);

        virtual ~Renderable2D();

        virtual void submit(Renderer2D *renderer) const
        {
            renderer->submit(this);
        };

    public:
        inline const maths::vec3 &getPosition() const { return m_Position; };
        inline const maths::vec2 &getSize() const { return m_Size; };
        inline const maths::vec4 &getColor() const { return m_Color; };
    };
} // namespace sparky::graphics{}
