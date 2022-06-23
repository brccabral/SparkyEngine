#pragma once

#include "renderable2d.h"
#include <string.h>

namespace sparky::graphics
{
	class Label: public Renderable2D
	{
	private:
		std::string m_Text;
	public:
		Label(std::string text, float x, float y, maths::vec4 color);
		void submit(Renderer2D *renderer) const override;
	};
}