#pragma once

#ifdef SPARKY_EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h> // need to include before GLFW
#endif

#include <vector>
#include <iostream>
#include "../utils/fileutils.h"
#include "../maths/maths.h"

namespace sparky
{
	namespace graphics
	{
		class Shader
		{
		private:
			const char *m_VertPath;
			const char *m_FragPath;

		public:
			Shader(const char *vertPath, const char *fragPath);
			~Shader();

			GLuint m_ShaderID; // shader ID given by openGl

			void enable() const;
			void disable() const;

			void setUniform(const GLchar *name, const maths::mat4 &matrix);
			void setUniform(const GLchar *name, int value);
			void setUniform(const GLchar *name, int *value, int count);
			void setUniform(const GLchar *name, float value);
			void setUniform(const GLchar *name, float *value, int count);
			void setUniform(const GLchar *name, const maths::vec2 &vector);
			void setUniform(const GLchar *name, const maths::vec3 &vector);
			void setUniform(const GLchar *name, const maths::vec4 &vector);

		private:
			GLuint load();

			GLint getUniformLocation(const GLchar *name);
		};
	}
}