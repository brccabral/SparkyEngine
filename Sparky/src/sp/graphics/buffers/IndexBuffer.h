#pragma once

#include <sp/sparky_types.h>
#include "../SPRenderAPI.h"

namespace sp
{
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			API::Buffer *m_Buffer;
			uint m_Count;

		public:
			IndexBuffer(short *data, uint count);
			IndexBuffer(uint *data, uint count);
			~IndexBuffer();

			void Bind() const;
			void Unbind() const;

			inline uint GetCount() const { return m_Count; }
		};
	}
}