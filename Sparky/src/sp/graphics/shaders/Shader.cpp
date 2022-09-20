#include "Shader.h"

namespace sp
{
	namespace graphics
	{
		Shader::Shader(const String &name, const String &source)
			: m_Name(name), m_Source(source)
		{
			String **shaders = new String * [2];
			shaders[0] = &m_VertexSource;
			shaders[1] = &m_FragmentSource;
			PreProcess(source, shaders);
			m_ShaderID = Load(m_VertexSource, m_FragmentSource);
			ResolveUniforms();
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

		void Shader::SetUniform(uint location, const maths::mat4 &matrix)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements);
		};
		void Shader::SetUniform(uint location, int value)
		{
			glUniform1i(location, value);
		};
		void Shader::SetUniform(uint location, int *value, int count)
		{
			glUniform1iv(location, count, value);
		};
		void Shader::SetUniform(uint location, float value)
		{
			glUniform1f(location, value);
		};
		void Shader::SetUniform(uint location, float *value, int count)
		{
			glUniform1fv(location, count, value);
		};
		void Shader::SetUniform(uint location, const maths::vec2 &vector)
		{
			glUniform2f(location, vector.x, vector.y);
		};
		void Shader::SetUniform(uint location, const maths::vec3 &vector)
		{
			glUniform3f(location, vector.x, vector.y, vector.z);
		};
		void Shader::SetUniform(uint location, const maths::vec4 &vector)
		{
			glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
		};

		void Shader::PreProcess(const String &source, String **shaders)
		{
			ShaderType type = ShaderType::UNKNOWN;

			std::vector<String> lines = utils::SplitString(source, '\n');
			for (uint i = 0; i < lines.size(); i++)
			{
				const char *str = lines[i].c_str();
				if (strstr(str, "#shader"))
				{
					if (strstr(str, "vertex"))
						type = ShaderType::VERTEX;
					else if (strstr(str, "fragment"))
						type = ShaderType::FRAGMENT;
				}
				else if (type != ShaderType::UNKNOWN)
				{
					shaders[(int)type - 1]->append(str);
					shaders[(int)type - 1]->append("\n");
				}
			}
			ParseUniforms(lines);
		}

		void Shader::ParseUniforms(const std::vector<String> &lines)
		{
			for (uint i = 0; i < lines.size(); i++)
			{
				const char *str = lines[i].c_str();
				if (strstr(str, "uniform"))
				{
					std::vector<String> line = utils::SplitString(str, ' ');
					for (uint i = 0; i < line.size(); i++)
					{
						// TODO: Precision
						String &token = line[i];
						ShaderUniformDeclaration::Type type = GetUniformTypeFromString(token);
						if (type != ShaderUniformDeclaration::Type::NONE)
						{
							String &nextToken = line[i + 1];
							String name = nextToken;
							if (name[name.size() - 1] == ';')
								name = nextToken.substr(0, nextToken.size() - 1);

							uint count = 1;

							// Uniform arrays
							uint arrayToken = nextToken.find('[');
							if (arrayToken != String::npos)
							{
								name = name.substr(0, arrayToken - 1);
								uint arrayEnd = nextToken.find(']');
								SPARKY_ASSERT(arrayEnd != String::npos);
								count = atoi(nextToken.substr(arrayToken + 1, arrayEnd - arrayToken - 1).c_str());
							}

							ShaderUniformDeclaration *uniform = new ShaderUniformDeclaration(type, name, this, count);
							m_Uniforms.push_back(uniform);
							break;
						}
					}
				}
			}
		}

		ShaderUniformDeclaration::Type Shader::GetUniformTypeFromString(const String &token)
		{
			if (token == "float") return ShaderUniformDeclaration::Type::FLOAT32;
			if (token == "int") return ShaderUniformDeclaration::Type::INT32;
			if (token == "vec2") return ShaderUniformDeclaration::Type::VEC2;
			if (token == "vec3") return ShaderUniformDeclaration::Type::VEC3;
			if (token == "vec4") return ShaderUniformDeclaration::Type::VEC4;
			if (token == "mat3") return ShaderUniformDeclaration::Type::MAT3;
			if (token == "mat4") return ShaderUniformDeclaration::Type::MAT4;
			if (token == "sampler2D") return ShaderUniformDeclaration::Type::SAMPLER2D;

			return ShaderUniformDeclaration::Type::NONE;
		}

		void Shader::ResolveUniforms()
		{
			uint offset = 0;
			for (uint i = 0; i < m_Uniforms.size(); i++)
			{
				ShaderUniformDeclaration *uniform = m_Uniforms[i];
				uniform->m_Offset = offset;
				uniform->m_Location = GetUniformLocation(uniform->m_Name);

				offset += uniform->GetSize();
			}
		}

		void Shader::ResolveAndSetUniforms(byte *data, uint size)
		{
			const std::vector<ShaderUniformDeclaration *> &uniforms = m_Uniforms;

			for (uint i = 0; i < uniforms.size(); i++)
				ResolveAndSetUniform(uniforms[i], data);
		}

		void Shader::ResolveAndSetUniform(ShaderUniformDeclaration *uniform, byte *data)
		{
			switch (uniform->GetType())
			{
			case ShaderUniformDeclaration::Type::FLOAT32:
				SetUniform(uniform->GetLocation(), *(float *)&data[uniform->GetOffset()]);
				break;
			case ShaderUniformDeclaration::Type::SAMPLER2D:
			case ShaderUniformDeclaration::Type::INT32:
				SetUniform(uniform->GetLocation(), *(int *)&data[uniform->GetOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC2:
				SetUniform(uniform->GetLocation(), *(maths::vec2 *)&data[uniform->GetOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC3:
				SetUniform(uniform->GetLocation(), *(maths::vec3 *)&data[uniform->GetOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC4:
				SetUniform(uniform->GetLocation(), *(maths::vec4 *)&data[uniform->GetOffset()]);
				break;
			case ShaderUniformDeclaration::Type::MAT3:
				// TODO: SetUniformMat3(uniform->GetLocation(), *(maths::mat3*)&data[uniform->GetOffset()]);
				break;
			case ShaderUniformDeclaration::Type::MAT4:
				SetUniform(uniform->GetLocation(), *(maths::mat4 *)&data[uniform->GetOffset()]);
				break;
			default:
				SPARKY_ASSERT(false, "Unknown type!");
			}
		}
	}
}