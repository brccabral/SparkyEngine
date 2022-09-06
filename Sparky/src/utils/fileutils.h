#pragma once

#include <string>
#include <fstream>
#include <utils/Log.h>

namespace sparky
{
	static std::string read_file(const std::string &filepath)
	{
		std::string content(
			std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
			std::istreambuf_iterator<char>());
		
		std::string message = "Couldn't read file " + filepath;
		SPARKY_ASSERT(content.size() != 0, message.c_str());
		
		return content;
	}
} // namespace sparky
