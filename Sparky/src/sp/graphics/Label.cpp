#include "Label.h"

namespace sp
{
	namespace graphics
	{
		Label::Label(String text, float x, float y, uint color)
			: Renderable2D(), text(text), x(x), y(y), position(m_Position), m_Font(FontManager::Get("SourceSansPro"))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
		};

		Label::Label(String text, float x, float y, Font *font, uint color)
			: Renderable2D(), text(text), x(x), y(y), position(m_Position), m_Font(font)
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
		};

		Label::Label(String text, float x, float y, const String &fontname, uint color)
			: Renderable2D(), text(text), x(x), y(y), position(m_Position), m_Font(FontManager::Get(fontname))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;

			Validatefont(fontname);
		};

		Label::Label(String text, float x, float y, const String &fontname, float size, uint color)
			: Renderable2D(), text(text), x(x), y(y), position(m_Position), m_Font(FontManager::Get(fontname, size))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;

			Validatefont(fontname, size);
		};

		void Label::Validatefont(const String &name, float size)
		{
			if (m_Font != nullptr)
				return;

			SP_WARN("NULL FONT! Font=", name.c_str(), ", Size=", size);

			m_Font = FontManager::Get("SourceSansPro");
		}

		void Label::Submit(Renderer2D *renderer) const
		{
			renderer->DrawString(text, position, *m_Font, m_Color);
		};
	}
}