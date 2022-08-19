#pragma once

#include <string>

#ifdef SPARKY_EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h> // need to include before GLFW
#endif

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

		inline const unsigned int getWidth() const { return m_Width; };
		inline const unsigned int getHeight() const { return m_Height; };
		inline const unsigned int getID() const { return m_TID; };

	private:
		GLuint load();
	};
}