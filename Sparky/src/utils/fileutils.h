#pragma once

#include <string>

namespace sparky
{
	class FileUtils
	{
	public:
		static std::string read_file(const std::string &filepath);
	};
} // namespace sparky
