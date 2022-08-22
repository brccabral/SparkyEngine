#pragma once

#ifdef SPARKY_EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#else
#include <GL/glew.h> // need to include before GLFW
#endif

#include <GLFW/glfw3.h>

namespace sparky
{
	namespace graphics
	{
		class Buffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_ComponentCount;

		public:
			Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
			~Buffer();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return m_ComponentCount; };
		};

	}
}