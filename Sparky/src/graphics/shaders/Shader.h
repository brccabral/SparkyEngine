#pragma once

#include <sparkygl.h>
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>
#include "../../utils/FileUtils.h"
#include "../../maths/maths.h"

namespace sparky
{
	namespace graphics
	{
	#define SHADER_VERTEX_INDEX		0
	#define SHADER_UV_INDEX			1
	#define SHADER_MASK_UV_INDEX	2
	#define SHADER_TID_INDEX		3
	#define SHADER_MID_INDEX		4
	#define SHADER_COLOR_INDEX		5

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

			void Bind() const;
			void Unbind() const;

			void SetUniform(const GLchar *name, const maths::mat4 &matrix);
			void SetUniform(const GLchar *name, int value);
			void SetUniform(const GLchar *name, int *value, int count);
			void SetUniform(const GLchar *name, float value);
			void SetUniform(const GLchar *name, float *value, int count);
			void SetUniform(const GLchar *name, const maths::vec2 &vector);
			void SetUniform(const GLchar *name, const maths::vec3 &vector);
			void SetUniform(const GLchar *name, const maths::vec4 &vector);

		private:
			GLuint Load(const char *vertSource, const char *fragSource);

			GLint GetUniformLocation(const GLchar *name);
		public:
			static Shader *FromFile(const char *vertPath, const char *fragPath);
			static Shader *FromSource(const char *vertSrc, const char *fragSrc);
			static Shader *FromSource(const char *name, const char *vertSrc, const char *fragSrc);
		};
	}
}