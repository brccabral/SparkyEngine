#pragma once

#include "sp/Common.h"
#include "Renderer2D.h" // must come before Buffer.h
#include "buffers/Buffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "Texture.h"
#include "../maths/maths.h"
#include "shaders/Shader.h"

namespace sp
{
	namespace graphics
	{
		struct SP_API VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv; // texture coordinates
			maths::vec2 mask_uv;
			float tid; // texture id
			float mid; // mask id
			uint color;
		};

	#define RENDERER_VERTEX_SIZE sizeof(VertexData)

		class SP_API Renderable2D
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

			virtual void Submit(Renderer2D *renderer) const
			{
				renderer->Submit(this);
			};

			void SetColor(uint color)
			{
				m_Color = color;
			}
			void SetColor(const maths::vec4 &color)
			{
				uint r = (uint)(color.x * 255.0f);
				uint g = (uint)(color.y * 255.0f);
				uint b = (uint)(color.z * 255.0f);
				uint a = (uint)(color.w * 255.0f);

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const maths::vec3 &GetPosition() const { return m_Position; };
			inline const maths::vec2 &GetSize() const { return m_Size; };
			inline const uint GetColor() const { return m_Color; };
			inline const std::vector<maths::vec2> &GetUV() const { return m_UV; };

			inline const GLuint GetTID() const { return m_Texture ? m_Texture->GetID() : 0; };
			inline const Texture *GetTexture() const { return m_Texture; };

		private:
			void SetUVDefaults();
		};
	}
}