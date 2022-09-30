#pragma once

#include "sp/sp.h"
#include <sp/Types.h>
#include "Buffer.h"

namespace sp
{
	namespace graphics
	{
		class SP_API VertexArray
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

			void Draw(uint count) const;
		};
	}
}