#pragma once

#include "Renderable2D.h"

namespace sp
{
	namespace graphics
	{
		class SP_API Sprite : public Renderable2D
		{
		public:
			Sprite(float x, float y, float width, float height, uint color);
			Sprite(float x, float y, float width, float height, Texture *texture);
			Sprite(Texture *texture);
			Sprite(float x, float y, Texture *texture);
			Sprite(float x, float y, float width, float height, const maths::vec4 &color);

			maths::vec3 &position;
			maths::vec2 &size;

			void SetUV(const std::vector<maths::vec2> &uv);

			inline void SetTexture(Texture *texture) { m_Texture = texture; }
		};

	}
}
