#pragma once

#include <string.h>
#include "renderable2d.h"
#include "font_manager.h"

namespace sparky
{
	namespace graphics
	{
		class Label : public Renderable2D
		{
		public:
			std::string text;
			maths::vec3 &position;
			float x, y;
			Font *m_Font;
		public:
			Label(std::string text, float x, float y, unsigned int color);
			Label(std::string text, float x, float y, Font *font, unsigned int color);
			Label(std::string text, float x, float y, const std::string &fontname, unsigned int color);
			Label(std::string text, float x, float y, const std::string &fontname, unsigned int size, unsigned int color);
			void submit(Renderer2D *renderer) const override;

			void validatefont(const std::string &name, unsigned int size = -1);
		};
	}
}