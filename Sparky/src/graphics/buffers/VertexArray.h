#pragma once

#include <vector>
#include <sparky_types.h>
#include "Buffer.h"
#include "graphics/SPRenderAPI.h"

namespace sparky
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			uint m_ID;
			std::vector<API::Buffer *> m_Buffers;
			static uint s_CurrentBinding;

		public:
			VertexArray();
			~VertexArray();

			void PushBuffer(API::Buffer *buffer);
			void Bind() const;
			void Unbind() const;

			API::Buffer *GetBuffer(uint index = 0);
		};
	}
}