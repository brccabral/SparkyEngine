#pragma once

#include "Shader.h"

namespace sparky
{
	namespace graphics
	{
		namespace ShaderFactory
		{
			Shader *DefaultShader();
			Shader *BasicLightShader();
			Shader *SimpleShader();
		}
	}
}