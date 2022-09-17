#pragma once

#include <string>
#include <sp/utils/Log.h>
#include <sp/sparky_types.h>
#include "../../../ext/freetype-gl/freetype-gl.h"
#include "../maths/maths.h"

namespace sp
{
	namespace graphics
	{
		class Font
		{
		private:
			ftgl::texture_atlas_t *m_FTAtlas;
			ftgl::texture_font_t *m_FTFont;
			float m_Size;
			String m_Filename;
			String m_Name;

			maths::vec2 m_Scale;
		public:
			Font(const String &name, const String &filename, float size);
			Font(const String &name, const byte *data, uint datasize, float size);

			inline ftgl::texture_font_t *GetFTFont() const { return m_FTFont; }

			inline const uint GetID() const { return m_FTAtlas->id; }
			inline const String &GetName() const { return m_Name; }
			inline const String &GetFilename() const { return m_Filename; }
			inline const float &GetSize() const { return m_Size; }

			void SetScale(float x, float y);
			inline const maths::vec2 &GetScale() const { return m_Scale; }
		};
	}
}