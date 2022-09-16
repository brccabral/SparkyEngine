#pragma once

#include <vector>
#include <sparky_types.h>
#include <maths/maths.h>
#include <utils/Log.h>
#include <GL/glew.h>

namespace sparky
{
	namespace graphics
	{

		struct BufferLayoutType
		{
			String name;
			uint type;
			uint size;
			uint count;
			uint offset;
			bool normalized;
		};

		class BufferLayout
		{
		private:
			uint m_Size;
			std::vector<BufferLayoutType> m_Layout;
		public:
			BufferLayout();

			template<typename T>
			void Push(const String &name, uint count = 1, bool normalized = false)
			{
				SPARKY_ASSERT(false, "Unkown type!");
			}

			template<> void Push<float>(const String &name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(float) * count, count, normalized); }
			template<> void Push<uint>(const String &name, uint count, bool normalized) { Push(name, GL_UNSIGNED_INT, sizeof(uint) * count, count, normalized); }
			template<> void Push<byte>(const String &name, uint count, bool normalized) { Push(name, GL_UNSIGNED_BYTE, sizeof(byte) * count, count, normalized); }
			template<> void Push<maths::vec2>(const String &name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(maths::vec2) * count, 2 * count, normalized); }
			template<> void Push<maths::vec3>(const String &name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(maths::vec3) * count, 3 * count, normalized); }
			template<> void Push<maths::vec4>(const String &name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(maths::vec4) * count, 4 * count, normalized); }

			inline const std::vector<BufferLayoutType> &GetLayout() const { return m_Layout; }
			inline uint GetStride() const { return m_Size; }
		private:
			void Push(const String &name, uint type, uint size, uint count, bool normalized);
		};


	}
}