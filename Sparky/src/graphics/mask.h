#pragma once

#include "texture.h"
#include "../maths/maths.h"

namespace sparky
{
	namespace graphics
	{
		struct Mask
		{
			Texture *texture;
			maths::mat4 transform;

			Mask(Texture *texture, const maths::mat4 &transform = maths::mat4::identity())
				: texture(texture), transform(transform)
			{
			}

		};

	}
}