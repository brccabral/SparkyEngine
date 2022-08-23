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
		}

		void Font::setScale(float x, float y)
		{
			m_Scale = maths::vec2(x, y);
		}

		// new freetype-gl doesn't upload glyph to OpenGL
		// we need to do it
		void const Font::upload_glyph_to_gl() const
		{
			glBindTexture(GL_TEXTURE_2D, m_FTAtlas->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_FTAtlas->width, m_FTAtlas->height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, m_FTAtlas->data);
		}
	}
}