#pragma once

#include <vector>
#include "Font.h"

namespace sp
{
	namespace graphics
	{
		class FontManager
		{
		private:
			static std::vector<Font *> m_Fonts;

			FontManager() {};

		public:
			static void Add(Font *font);
			static Font *Get();
			static Font *Get(const String &name);
			static Font *Get(const String &name, float size);
			static void Clean();
		};
	}
}