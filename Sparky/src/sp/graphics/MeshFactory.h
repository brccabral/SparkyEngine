#pragma once

#include "sp/Common.h"
#include "sp/Types.h"
#include "sp/maths/maths.h"

#include "sp/graphics/buffers/VertexArray.h"
#include "sp/graphics/Mesh.h"
#include "sp/graphics/Material.h"

namespace sp
{
	namespace graphics
	{
		namespace MeshFactory
		{

			//
			// TODO: Perhaps this should return some sort of Mesh object with modifiable data.
			//		 For now it uploads data to the GPU and returns the handle.
			//

			SP_API VertexArray *CreateQuad(float x, float y, float width, float height);
			SP_API VertexArray *CreateQuad(const maths::vec2 &position, const maths::vec2 &size);

			SP_API Mesh *CreateCube(float size, MaterialInstance *material);
		}
	}
}