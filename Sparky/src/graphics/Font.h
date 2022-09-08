#pragma once

#include <string>
#include <utils/Log.h>
#include <sparky_types.h>
#include "../../ext/freetype-gl/freetype-gl.h"
#include "../maths/maths.h"

namespace sparky
{
	namespace graphics
	{
		class Font
		{
		private:
			ftgl::texture_atlas_t *m_FTAtlas;
			ftgl::texture_font_t *m_FTFont;
			float m_Size;
			std::string m_Filename;
			std::string m_Name;

			maths::vec2 m_Scale;
		public:
			Font(const std::string &name, const std::string &filename, float size);
			Font(const std::string &name, const byte *data, uint datasize, float size);

			inline ftgl::texture_font_t *getFTGLFont() const { return m_FTFont; }

			inline const uint getID() const { return m_FTAtlas->id; }
			inline const std::string &getName() const { return m_Name; }
			inline const std::string &getFilename() const { return m_Filename; }
			inline const float &getSize() const { return m_Size; }

			void setScale(float x, float y);
			inline const maths::vec2 &getScale() const { return m_Scale; }
		};
	}
}