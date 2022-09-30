#pragma once

#include <sp/utils/Log.h>

namespace sp
{
	namespace utils
	{
		static String ReadFile(const String &filepath)
		{
			String content(
				std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
				std::istreambuf_iterator<char>());

			SP_ASSERT(content.size() != 0, "Could not read file '", filepath.c_str(), "'!");

			return content;
		}
	}
} // namespace sp
