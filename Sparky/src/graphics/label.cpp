#include "label.h"

namespace sparky
{
	namespace graphics
	{
		Label::Label(std::string text, float x, float y, unsigned int color)
			: Renderable2D(), text(text), x(x), y(y), position(m_Position), m_Font(FontManager::get("SourceSansPro"))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
		};

		Label::Label(std::string text, float x, float y, Font *font, unsigned int color)
			: Renderable2D(), text(text), x(x), y(y), position(m_Position), m_Font(font)
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
		};

		Label::Label(std::string text, float x, float y, const std::string &fontname, unsigned int color)
			: Renderable2D(), text(text), x(x), y(y), position(m_Position), m_Font(FontManager::get(fontname))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;

			validatefont(fontname);
		};

		Label::Label(std::string text, float x, float y, const std::string &fontname, unsigned int size, unsigned int color)
			: Renderable2D(), text(text), x(x), y(y), position(m_Position), m_Font(FontManager::get(fontname, size))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;

			validatefont(fontname, size);
		};

		void Label::validatefont(const std::string &name, unsigned int size)
		{
			if (m_Font != nullptr)
				return;

			std::cout << "NULL FONT! Font=" << name;
			if (size > 0)
				std::cout << ", Size=" << size;
			std::cout << std::endl;

			m_Font = FontManager::get("SourceSansPro");
		}

		void Label::submit(Renderer2D *renderer) const
		{
			renderer->drawString(text, position, *m_Font, m_Color);
		};
	}
}