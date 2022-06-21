#pragma once

#include <GL/glew.h>
#include "../utils/fileutils.h"
#include "../maths/maths.h"

namespace sparky::graphics
{
	class Shader
	{
	private:
		const char *m_vertPath;
		const char *m_fragPath;

	public:
		Shader(const char *vertPath, const char *fragPath);
		~Shader();

		GLuint m_ShaderID; // shader ID given by openGl

		void enable() const;
		void disable() const;

		void setUniform(const GLchar *name, const maths::mat4 &matrix);
		void setUniform(const GLchar *name, int value);
		void setUniform(const GLchar *name, float value);
		void setUniform(const GLchar *name, const maths::vec2 &vector);
		void setUniform(const GLchar *name, const maths::vec3 &vector);
		void setUniform(const GLchar *name, const maths::vec4 &vector);

	private:
		GLuint load();

		GLint getUniformLocation(const GLchar *name);
	};
} // namespace sparky::graphics
