#include "font.h"

namespace sparky
{
	namespace graphics
	{
		Font::Font(std::string name, std::string filename, unsigned int size)
			: m_Name(name), m_Filename(filename), m_Size(size)
		{
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, filename.c_str());

			glGenTextures(1, &m_FTAtlas->id);
			glBindTexture(GL_TEXTURE_2D, m_FTAtlas->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_FTAtlas->width, m_FTAtlas->height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, m_FTAtlas->data);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_FTAtlas->width, m_FTAtlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, m_FTAtlas->data);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Font::setScale(float x, float y)
		{
			m_Scale = maths::vec2(x, y);
		}
	}
}