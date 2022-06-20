#pragma once

#include <GL/glew.h>
#include "../maths/maths.h"
#include "static_sprite.h"

namespace sparky::graphics
{
    class Renderer2D
    {
    public:
        virtual void begin() {};
        virtual void submit(const Renderable2D* renderable) = 0;
        virtual void end() {};
        virtual void flush() = 0;
    };
} // namespace sparky::graphics
