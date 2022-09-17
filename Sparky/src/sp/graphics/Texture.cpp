#include "Texture.h"

namespace sp
{
	namespace graphics
	{
		TextureWrap Texture::s_WrapMode = REPEAT;
		TextureFilter Texture::s_FilterMode = TextureFilter::LINEAR;

		Texture::Texture(const String &name, const String &filename)
			: m_Name(name), m_FileName(filename)
		{
			m_TID = Load();
		};

		// need 24 for Font, with 32 Font loses quality
		Texture::Texture(uint width, uint height, uint bits)
			: m_Width(width), m_Height(height), m_FileName("NULL"), m_Bits(24)
		{
			m_TID = Load();
		}

		Texture::~Texture()
		{
			API::FreeTexture(m_TID);
		};

		GLuint Texture::Load()
		{
			BYTE *pixels = nullptr;
			if (m_FileName != "NULL")
				pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height, &m_Bits);

			uint result = API::CreateTexture();
			API::BindTexture(GL_TEXTURE_2D, result);
			API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)s_FilterMode);
			API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)s_FilterMode);
			API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)s_WrapMode);
			API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)s_WrapMode);

			// Image needs to be 24 bits (RGB) or 32 bits (RGBA) - 8 bits per channel,  8*3 or 8*4
			if (m_Bits != 24 && m_Bits != 32)
				SPARKY_ERROR("[Texture] Unsupported image bit-depth! (", m_Bits, ")");

			int internalFormat = m_Bits == 32 ? GL_RGBA : GL_RGB;
			uint format = m_Bits == 32 ?
		#ifdef SPARKY_PLATFORM_WEB
				GL_RGBA : GL_RGB;
		#else
				// Emscripten swaps Red and Blue
			GL_BGRA: GL_BGR;
		#endif
			API::SetTextureData(GL_TEXTURE_2D, internalFormat, m_Width, m_Height, format, GL_UNSIGNED_BYTE, pixels ? pixels : NULL);
			API::UnbindTexture(GL_TEXTURE_2D);

			if (pixels != nullptr)
				delete[] pixels;

			return result;
		};

		void Texture::Bind() const
		{
			API::BindTexture(GL_TEXTURE_2D, m_TID);
		};
		void Texture::Unbind() const
		{
			API::UnbindTexture(GL_TEXTURE_2D);
		};
	}
}