#pragma once

#include <string>
#include <fstream>
#include <sp/utils/Log.h>

namespace sp
{
	static String read_file(const String &filepath)
	{
		String content(
			std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
			std::istreambuf_iterator<char>());

		SPARKY_ASSERT(content.size() != 0, "Could not read file '", filepath.c_str(), "'!");

		return content;
	}
} // namespace sp
