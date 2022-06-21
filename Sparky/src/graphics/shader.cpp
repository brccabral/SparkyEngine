#include "shader.h"
#include <vector>
#include <iostream>
#include "../maths/maths.h"

namespace sparky::graphics
{
	Shader::Shader(const char *vertPath, const char *fragPath)
		: m_vertPath(vertPath), m_fragPath(fragPath)
	{
		m_ShaderID = load();
	};

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::load()
	{
		// create a GL program
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		// read GL files
		// need to store the result before using it
		// or the read_file will delete from memory
		std::string vertSouceString = read_file(m_vertPath);
		std::string fragSouceString = read_file(m_fragPath);
		const char *vertSource = vertSouceString.c_str();
		const char *fragSource = fragSouceString.c_str();

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
	void Shader::setUniform(const GLchar *name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
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