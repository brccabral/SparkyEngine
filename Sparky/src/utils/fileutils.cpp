#include "fileutils.h"
#include <string>
#include <fstream>

namespace sparky
{
    std::string read_file(const std::string &filepath)
    {
        std::string content(
            std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
            std::istreambuf_iterator<char>());
        return content;
    }

} // namespace sparky
