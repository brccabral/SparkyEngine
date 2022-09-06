#include "shader.h"

namespace sparky
{
	namespace graphics
	{
		Shader::Shader(const char *name, const char *vertSrc, const char *fragSrc)
			: m_VertPath(nullptr), m_FragPath(nullptr), m_Name(name), m_VertSrc(vertSrc), m_FragSrc(fragSrc)
		{
			m_ShaderID = load(m_VertSrc, m_FragSrc);
		};

		Shader::Shader(const char *vertPath, const char *fragPath)
			: m_VertPath(vertPath), m_FragPath(fragPath), m_Name(vertPath), m_VertSrc(nullptr), m_FragSrc(nullptr)
		{
			// read GL files
			// need to store the result before using it
			// or the read_file will delete from memory
			std::string vertSourceString = read_file(m_VertPath);
			std::string fragSourceString = read_file(m_FragPath);
			m_VertSrc = vertSourceString.c_str();
			m_FragSrc = fragSourceString.c_str();

			m_ShaderID = load(m_VertSrc, m_FragSrc);
		};

		Shader *Shader::FromFile(const char *vertPath, const char *fragPath)
		{
			return new Shader(vertPath, fragPath);
		}
		
		Shader *Shader::FromSource(const char *vertSrc, const char *fragSrc)
		{
			return new Shader(vertSrc, vertSrc, fragSrc);
		}

		Shader *Shader::FromSource(const char *name, const char *vertSrc, const char *fragSrc)
		{
			return new Shader(name, vertSrc, fragSrc);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		GLuint Shader::load(const char *vertSource, const char *fragSource)
		{
			// create a GL program
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			// send GL file to openGL and compile
			glShaderSource(vertex, 1, &vertSource, NULL);
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
				std::cout << "Failed to compile vertex shader!" << std::endl
					<< &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			// send GL file to openGL and compile
			glShaderSource(fragment, 1, &fragSource, NULL);
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
				std::cout << "Failed to compile fragment shader!" << std::endl
					<< &error[0] << std::endl;
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

		void Shader::enable() const
		{
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

		GLint Shader::getUniformLocation(const GLchar *name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		};

		void Shader::setUniform(const GLchar *name, const maths::mat4 &matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		};
		void Shader::setUniform(const GLchar *name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		};
		void Shader::setUniform(const GLchar *name, int *value, int count)
		{
			glUniform1iv(getUniformLocation(name), count, value);
		};
		void Shader::setUniform(const GLchar *name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		};
		void Shader::setUniform(const GLchar *name, float *value, int count)
		{
			glUniform1fv(getUniformLocation(name), count, value);
		};
		void Shader::setUniform(const GLchar *name, const maths::vec2 &vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		};
		void Shader::setUniform(const GLchar *name, const maths::vec3 &vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		};
		void Shader::setUniform(const GLchar *name, const maths::vec4 &vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		};
	}
}