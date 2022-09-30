#pragma once

#include "sp/sp.h"

#include "../Framebuffer.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"
#include "PostEffectsPass.h"

namespace sp
{
	namespace graphics
	{

		// The Post Effects pipeline
		class SP_API PostEffects
		{
		private:
			std::vector<PostEffectsPass *> m_Passes;
		public:
			PostEffects();
			~PostEffects();
			void Push(PostEffectsPass *pass);
			void Pop();

			void RenderPostEffects(Framebuffer *source, Framebuffer *target, VertexArray *quad, IndexBuffer *indices);
		};

	}
}