#pragma once

// Instead of having a queue that renders sprites one by one
// add all sprites to one batch buffer and render them all at once

#include <cstddef>
#include <vector>
#include <string.h>
#include <sparky_types.h>
#include "renderer2d.h"
#include "renderable2d.h"
#include "buffers/indexbuffer.h"

namespace sparky
{
	namespace graphics
	{
	#define RENDERER_MAX_SPRITES 60000
	#define RENDERER_VERTEX_SIZE sizeof(VertexData)
	#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
	#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
	#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6
		// 32 max, but 1 for the mask
	#define RENDERER_MAX_TEXTURES 32 - 1

	#define SHADER_VERTEX_INDEX 0
	#define SHADER_UV_INDEX 1
	#define SHADER_TID_INDEX 2
	#define SHADER_COLOR_INDEX 3

		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer *m_IBO;
			GLsizei m_IndexCount;

			VertexData *m_Buffer;

			std::vector<GLuint> m_TextureSlots;

		#ifdef SPARKY_PLATFORM_WEB
			VertexData *m_BufferBase;
		#endif

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D *renderable) override;
			void end() override;
			void flush() override;

			void drawString(const std::string &text, maths::vec3 position, const Font &font, uint color) override;

		private:
			void init();
		};
	}
}