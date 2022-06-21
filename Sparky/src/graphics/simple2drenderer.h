#pragma once

#include <deque>
#include "renderer2d.h"
#include "static_sprite.h"
#include "renderable2d.h"

namespace sparky::graphics
{
	class Simple2Drenderer : public Renderer2D
	{
	private:
		std::deque<const StaticSprite *> m_RendererQueue;

	public:
		void submit(const Renderable2D *renderable) override;
		void flush() override;
	};
} // namespace sparky::graphics
