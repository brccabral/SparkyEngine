#pragma once

#include "sp/Common.h"
#include "sp/Types.h"
#include "sp/maths/vec2.h"
#include "sp/graphics/Texture.h"

namespace ftgl
{
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace sp
{
	namespace graphics
	{
		class SP_API Font
		{
		private:
			ftgl::texture_atlas_t *m_FTAtlas;
			ftgl::texture_font_t *m_FTFont;
			float m_Size;
			String m_Filename;
			String m_Name;

			maths::vec2 m_Scale;
			mutable Texture *m_Texture; // TODO: Replace with array
		public:
			Font(const String &name, const String &filename, float size);
			Font(const String &name, const byte *data, uint datasize, float size);

			inline ftgl::texture_font_t *GetFTFont() const { return m_FTFont; }

			uint GetID() const;
			inline const String &GetName() const { return m_Name; }
			inline const String &GetFilename() const { return m_Filename; }
			inline float GetSize() const { return m_Size; }

			inline void SetScale(const maths::vec2 &scale) { m_Scale = scale; }
			void SetScale(float x, float y);
			inline const maths::vec2 &GetScale() const { return m_Scale; }
			Texture *GetTexture() const;
		};
	}
}