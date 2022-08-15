#include "fileutils.h"

namespace sparky
{
	std::string FileUtils::read_file(const std::string &filepath)
	{
		std::string content(
			std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
			std::istreambuf_iterator<char>());
		return content;
	}
} // namespace sparky
