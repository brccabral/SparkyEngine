#pragma once

#include <sparkygl.h>
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>
#include "../../utils/fileutils.h"
#include "../../maths/maths.h"

namespace sparky
{
	namespace graphics
	{
		class Shader
		{
		private:
			const char *m_Name;
			const char *m_VertPath;
			const char *m_FragPath;
			const char *m_VertSrc;
			const char *m_FragSrc;

		public:
			Shader(const char *name, const char *vertSrc, const char *fragSrc);
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
			GLuint load(const char *vertSource, const char *fragSource);

			GLint getUniformLocation(const GLchar *name);
		public:
			static Shader *FromFile(const char *vertPath, const char *fragPath);
			static Shader *FromSource(const char *vertSrc, const char *fragSrc);
			static Shader *FromSource(const char *name, const char *vertSrc, const char *fragSrc);
		};
	}
}