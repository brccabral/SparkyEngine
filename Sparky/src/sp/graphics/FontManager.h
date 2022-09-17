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
			static Font *Get(const std::string &name);
			static Font *Get(const std::string &name, float size);
			static void Clean();
		};
	}
}