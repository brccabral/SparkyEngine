#pragma once

#include <string.h>
#include "Renderable2D.h"
#include "FontManager.h"

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
			Label(std::string text, float x, float y, uint color);
			Label(std::string text, float x, float y, Font *font, uint color);
			Label(std::string text, float x, float y, const std::string &fontname, uint color);
			Label(std::string text, float x, float y, const std::string &fontname, float size, uint color);
			void Submit(Renderer2D *renderer) const override;

			void Validatefont(const std::string &name, float size = -1.0f);
		};
	}
}