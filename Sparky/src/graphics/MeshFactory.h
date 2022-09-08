#pragma once

#include <sparky_types.h>
#include <maths/maths.h>
#include <sparkygl.h>
#include <graphics/Renderable2D.h>
#include <graphics/shaders/Shader.h>

namespace sparky
{
	namespace graphics
	{
		namespace MeshFactory
		{

			//
			// TODO: Perhaps this should return some sort of Mesh object with modifiable data.
			//		 For now it uploads data to the GPU and returns the handle.
			//

			uint CreateQuad(float x, float y, float width, float height);
			uint CreateQuad(const maths::vec2 &position, const maths::vec2 &size);

		}
	}
}