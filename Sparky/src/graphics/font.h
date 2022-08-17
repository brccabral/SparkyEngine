#pragma once

#include <string>
#include "../../ext/freetype-gl/freetype-gl.h"

namespace sparky::graphics
{
	class Font
	{
	private:
		ftgl::texture_atlas_t *m_FTAtlas;
		ftgl::texture_font_t *m_FTFont;
		unsigned int m_Size;
		std::string m_Filename;
		std::string m_Name;
	public:
		Font(std::string name, std::string filename, unsigned int size);

		inline ftgl::texture_font_t *getFTGLFont() const { return m_FTFont; }

		inline const unsigned int getID() const { return m_FTAtlas->id; }
		inline const std::string &getName() const { return m_Name; }
		inline const std::string &getFilename() const { return m_Filename; }
		inline const unsigned int &getSize() const { return m_Size; }
	};
}