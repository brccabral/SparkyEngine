#pragma once

#include <iostream>
#include <string>
#include <utils/Log.h> // needs to be before GL, redefinition of APIENTRY
#include "SPRenderAPI.h"
#include <utils/ImageLoad.h>
#include <GL/glew.h>

namespace sparky
{
	namespace graphics
	{
		enum TextureWrap
		{
			REPEAT = GL_REPEAT,
			CLAMP = GL_CLAMP,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
		};

		enum class TextureFilter
		{
			LINEAR = GL_LINEAR,
			NEAREST = GL_NEAREST
		};

		class Texture
		{
		private:
			std::string m_Name, m_FileName;
			uint m_TID;
			uint m_Width, m_Height;
			uint m_Bits;
			static TextureWrap s_WrapMode;
			static TextureFilter s_FilterMode;
		public:
			Texture(const std::string &name, const std::string &filename);
			Texture(uint width, uint height, uint bits = 24);
			~Texture();
			void Bind() const;
			void Unbind() const;

			inline const uint GetWidth() const { return m_Width; };
			inline const uint GetHeight() const { return m_Height; };
			inline const uint GetID() const { return m_TID; };
			inline const std::string &GetName() const { return m_Name; };

			inline static void SetWrap(TextureWrap mode) { s_WrapMode = mode; };
			inline static void SetFilter(TextureFilter mode) { s_FilterMode = mode; }
		private:
			GLuint Load();
		};
	}
}