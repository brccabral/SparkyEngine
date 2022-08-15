#pragma once

#include <string>
#include <fstream>

namespace sparky
{
	class FileUtils
	{
	public:
		static std::string read_file(const std::string &filepath);
	};
} // namespace sparky
