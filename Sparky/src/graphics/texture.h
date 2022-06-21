#pragma once

#include <string>
#include <GL/glew.h>
#include <FreeImage.h>
#include "../utils/imageload.h"

namespace sparky::graphics
{
	class Texture
	{
	private:
		std::string m_FileName;
		GLuint m_TID;
		GLsizei m_Width, m_Height;

	public:
		Texture(const std::string &filename);
		~Texture();
		void bind() const;
		void unbind() const;

		inline unsigned int getWidth() { return m_Width; };
		inline unsigned int getHeight() { return m_Height; };

	private:
		GLuint load();
	};
}