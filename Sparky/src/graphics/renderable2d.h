#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "renderer2d.h"
#include "texture.h"
#include "../maths/maths.h"
#include "shader.h"

namespace sparky
{
	namespace graphics
	{
		struct VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv; // texture coordinates
			float tid;
			uint color;
		};

		class Renderable2D
		{
		protected:
			maths::vec3 m_Position;
			maths::vec2 m_Size;
			uint m_Color;
			std::vector<maths::vec2> m_UV;
			Texture *m_Texture;

			Renderable2D();

		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, uint color);

			virtual ~Renderable2D();

			virtual void submit(Renderer2D *renderer) const
			{
				renderer->submit(this);
			};

			void setColor(uint color)
			{
				m_Color = color;
			}
			void setColor(const maths::vec4 &color)
			{
				uint r = (uint)(color.x * 255.0f);
				uint g = (uint)(color.y * 255.0f);
				uint b = (uint)(color.z * 255.0f);
				uint a = (uint)(color.w * 255.0f);

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const maths::vec3 &getPosition() const { return m_Position; };
			inline const maths::vec2 &getSize() const { return m_Size; };
			inline const uint getColor() const { return m_Color; };
			inline const std::vector<maths::vec2> &getUV() const { return m_UV; };

			inline const GLuint getTID() const { return m_Texture ? m_Texture->getID() : 0; };

		private:
			void setUVDefaults();
		};
	}
}