#pragma once

#include <string>
#include <fstream>
#include <sp/utils/Log.h>

namespace sparky
{
	static std::string read_file(const std::string &filepath)
	{
		std::string content(
			std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
			std::istreambuf_iterator<char>());

		SPARKY_ASSERT(content.size() != 0, "Could not read file '", filepath.c_str(), "'!");

		return content;
	}
} // namespace sparky
