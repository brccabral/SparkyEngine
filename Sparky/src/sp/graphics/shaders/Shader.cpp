#include "Shader.h"

namespace sp
{
	namespace graphics
	{
		Shader::Shader(const String &name, const String &source)
			: m_Name(name), m_Source(source)
		{
			String shaders[2];
			PreProcess(source, shaders);
			m_ShaderID = Load(shaders[0], shaders[1]);
		}

		Shader *Shader::FromFile(const String &name, const String &filepath)
		{
			String shader = utils::ReadFile(filepath);
			return new Shader(name, shader);
		}

		Shader *Shader::FromSource(const String &name, const String &source)
		{
			return new Shader(name, source);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		uint Shader::Load(const String &vertSource, const String &fragSource)
		{
			const char *vertexSource = vertSource.c_str();
			const char *fragmentSource = fragSource.c_str();

			// create a GL program
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			// send GL file to openGL and compile

			glShaderSource(vertex, 1, &vertexSource, NULL);
			glCompileShader(vertex);

			GLint result;
			// check result of compilation
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			// check if any errors during compile
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				SPARKY_ERROR("Failed to compile vertex shader! ", m_Name);
				SPARKY_ERROR(&error[0]);
				SPARKY_ASSERT(false, "Failed to compile vertex shader!");
				glDeleteShader(vertex);
				return 0;
			}

			// send GL file to openGL and compile
			glShaderSource(fragment, 1, &fragmentSource, NULL);
			glCompileShader(fragment);

			// check result of compilation
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			// check if any errors during compile
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				SPARKY_ERROR("Failed to compile fragment shader! ", m_Name);
				SPARKY_ERROR(&error[0]);
				SPARKY_ASSERT(false, "Failed to fragment vertex shader!");
				glDeleteShader(fragment);
				return 0;
			}
			// attach shaders to program
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			// link and validate program
			glLinkProgram(program);
			glValidateProgram(program);
			// clear memory
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		void Shader::Bind() const
		{
			glUseProgram(m_ShaderID);
		}

		void Shader::Unbind() const
		{
			glUseProgram(0);
		}

		int Shader::GetUniformLocation(const String &name)
		{
			GLint result = glGetUniformLocation(m_ShaderID, name.c_str());
			if (result == -1)
				SPARKY_ERROR(m_Name, ": could not find uniform ", name, " in shader!");

			return result;
		};

		void Shader::SetUniform(const String &name, const maths::mat4 &matrix)
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
		};
		void Shader::SetUniform(const String &name, int value)
		{
			glUniform1i(GetUniformLocation(name), value);
		};
		void Shader::SetUniform(const String &name, int *value, int count)
		{
			glUniform1iv(GetUniformLocation(name), count, value);
		};
		void Shader::SetUniform(const String &name, float value)
		{
			glUniform1f(GetUniformLocation(name), value);
		};
		void Shader::SetUniform(const String &name, float *value, int count)
		{
			glUniform1fv(GetUniformLocation(name), count, value);
		};
		void Shader::SetUniform(const String &name, const maths::vec2 &vector)
		{
			glUniform2f(GetUniformLocation(name), vector.x, vector.y);
		};
		void Shader::SetUniform(const String &name, const maths::vec3 &vector)
		{
			glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
		};
		void Shader::SetUniform(const String &name, const maths::vec4 &vector)
		{
			glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		};

		void Shader::PreProcess(const String &source, String *shaders)
		{
			ShaderType type = ShaderType::UNKNOWN;

			std::vector<String> lines = utils::SplitString(source, '\n');
			for (uint i = 0; i < lines.size(); i++)
			{
				const char *str = lines[i].c_str();
				const char *res = strstr(str, "#shader");
				if (res != NULL)
				{
					if (strstr(str, "vertex"))
						type = ShaderType::VERTEX;
					else if (strstr(str, "fragment"))
						type = ShaderType::FRAGMENT;
				}
				else if (type != ShaderType::UNKNOWN)
				{
					shaders[(int)type - 1].append(str);
					shaders[(int)type - 1].append("\n");
				}
			}
		}
	}
}