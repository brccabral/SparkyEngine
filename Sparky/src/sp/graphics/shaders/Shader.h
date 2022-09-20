#pragma once

#include <vector>
#include <iostream>
#include <sp/utils/FileUtils.h>
#include <sp/utils/StringUtils.h>
#include <sp/maths/maths.h>

namespace sp
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
			enum class ShaderType
			{
				UNKNOWN, VERTEX, FRAGMENT
			};
			struct ShaderSource
			{

			};

			String m_Name, m_Path;
			String m_Source;
			uint m_ShaderID; // shader ID given by openGl
		public:
			Shader(const String &name, const String &source);
			~Shader();


			void Bind() const;
			void Unbind() const;

			void SetUniform(const String &name, const maths::mat4 &matrix);
			void SetUniform(const String &name, int value);
			void SetUniform(const String &name, int *value, int count);
			void SetUniform(const String &name, float value);
			void SetUniform(const String &name, float *value, int count);
			void SetUniform(const String &name, const maths::vec2 &vector);
			void SetUniform(const String &name, const maths::vec3 &vector);
			void SetUniform(const String &name, const maths::vec4 &vector);

		private:
			uint Load(const String &vertSource, const String &fragSource);

			int GetUniformLocation(const String &name);

			void PreProcess(const String &source, String *shaders);
		public:
			static Shader *FromFile(const String &name, const String &filepath);
			static Shader *FromSource(const String &name, const String &source);
		};
	}
}