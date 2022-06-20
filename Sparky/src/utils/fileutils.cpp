#include "fileutils.h"
#include <string>
#include <string.h>

namespace sparky
{
    std::string read_file(const char* filepath)
    {
        FILE* file = fopen(filepath, "rt"); // rt = read as text (line ending is like text file)
        fseek(file, 0, SEEK_END);

        unsigned long length = ftell(file); // get number of bytes
        char* data = new char[length + 1];  // allocate in HEAP

        memset(data, 0, length + 1);  // set all to 0
        fseek(file, 0, SEEK_SET);     // go back to beginning
        fread(data, 1, length, file); // read file and put in data, 1 byte = sizeof(char)
        fclose(file);

        std::string result(data);

        // delete from HEAP
        delete[] data;

        return result;
    }
} // namespace sparky
