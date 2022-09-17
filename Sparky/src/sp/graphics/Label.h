#pragma once

#include <string.h>
#include "Renderable2D.h"
#include "FontManager.h"

namespace sp
{
	namespace graphics
	{
		class Label : public Renderable2D
		{
		public:
			String text;
			maths::vec3 &position;
			float x, y;
			Font *m_Font;
		public:
			Label(String text, float x, float y, uint color);
			Label(String text, float x, float y, Font *font, uint color);
			Label(String text, float x, float y, const String &fontname, uint color);
			Label(String text, float x, float y, const String &fontname, float size, uint color);
			void Submit(Renderer2D *renderer) const override;

			void Validatefont(const String &name, float size = -1.0f);
		};
	}
}