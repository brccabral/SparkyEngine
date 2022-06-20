#pragma once

#include <deque>
#include "renderer2d.h"

namespace sparky::graphics
{
    class Simple2Drenderer : public Renderer2D
    {
    private:
        std::deque<const Renderable2D*> m_RendererQueue;

    public:
        void submit(Renderable2D* renderable) override;
        void flush() override;
    };
} // namespace sparky::graphics
