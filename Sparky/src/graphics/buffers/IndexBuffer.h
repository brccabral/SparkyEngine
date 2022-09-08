#pragma once

#include <sparkygl.h>
#include <sparky_types.h>

namespace sparky
{
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLsizei m_Count;

		public:
			IndexBuffer(short *data, uint count);
			IndexBuffer(uint *data, uint count);
			~IndexBuffer();

			void Bind() const;
			void Unbind() const;

			inline GLsizei GetCount() const { return m_Count; };
		};
	}
}