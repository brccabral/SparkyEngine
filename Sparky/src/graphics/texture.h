#pragma once

#include <iostream>
#include <string>
#include <utils/Log.h> // needs to be before GL, redefinition of APIENTRY
#include <sparkygl.h>
#include <utils/imageload.h>

namespace sparky
{
	namespace graphics
	{
		enum TextureWrap
		{
			REPEAT = 0x2901,
			CLAMP = 0x2900,
			MIRRORED_REPEAT = 0x8370,
			CLAMP_TO_EDGE = 0x812F,
			CLAMP_TO_BORDER = 0x812D
		};

		class Texture
		{
		private:
			std::string m_Name, m_FileName;
			GLuint m_TID;
			GLsizei m_Width, m_Height;
			uint m_Bits;
			static TextureWrap s_WrapMode;
		public:
			Texture(const std::string &name, const std::string &filename);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const uint getWidth() const { return m_Width; };
			inline const uint getHeight() const { return m_Height; };
			inline const uint getID() const { return m_TID; };
			inline const std::string &getName() const { return m_Name; };

			inline static void SetWrap(TextureWrap mode) { s_WrapMode = mode; };
		private:
			GLuint load();
		};
	}
}