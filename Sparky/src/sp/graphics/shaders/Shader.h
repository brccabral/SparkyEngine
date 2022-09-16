#pragma once

#include <vector>
#include <iostream>
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

			uint m_ShaderID; // shader ID given by openGl
		public:
			Shader(const char *name, const char *vertSrc, const char *fragSrc);
			Shader(const char *vertPath, const char *fragPath);
			~Shader();


			void Bind() const;
			void Unbind() const;

			void SetUniform(const char *name, const maths::mat4 &matrix);
			void SetUniform(const char *name, int value);
			void SetUniform(const char *name, int *value, int count);
			void SetUniform(const char *name, float value);
			void SetUniform(const char *name, float *value, int count);
			void SetUniform(const char *name, const maths::vec2 &vector);
			void SetUniform(const char *name, const maths::vec3 &vector);
			void SetUniform(const char *name, const maths::vec4 &vector);

		private:
			uint Load(const char *vertSource, const char *fragSource);

			int GetUniformLocation(const char *name);
		public:
			static Shader *FromFile(const char *vertPath, const char *fragPath);
			static Shader *FromSource(const char *vertSrc, const char *fragSrc);
			static Shader *FromSource(const char *name, const char *vertSrc, const char *fragSrc);
		};
	}
}