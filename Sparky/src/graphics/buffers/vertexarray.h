#pragma once

#include <vector>

#ifdef SPARKY_EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h> // need to include before GLFW
#endif

#include "buffer.h"

namespace sparky::graphics
{
	class VertexArray
	{
	private:
		GLuint m_ArrayID;
		std::vector<Buffer *> m_Buffers;

	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer *buffer, GLuint index);
		void bind() const;
		void unbind() const;
	};
}