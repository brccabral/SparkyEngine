#include "fileutils.h"
#include <string>
#include <fstream>

namespace sparky
{
    std::string read_file(const std::string& filepath)
    {
        std::ifstream ifs((filepath).c_str());
        std::string content(
            std::istreambuf_iterator<char>(ifs.rdbuf()),
            std::istreambuf_iterator<char>());
        return content;
    }

} // namespace sparky
