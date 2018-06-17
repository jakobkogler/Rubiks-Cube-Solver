#include "fileio.h"
#include <fstream>

void FileIO::store_char_vector(std::vector<char> &vec, std::string path)
{
    std::ofstream file(path.c_str(), std::ios::out | std::ofstream::binary);
    file.write(&vec[0], vec.size()*sizeof(char));
    file.close();
}

bool FileIO::read_char_vector(std::vector<char> &vec, std::string path, int required_size)
{
    std::ifstream file(path.c_str(), std::ios::binary);
    if (file.good())
    {
        vec.reserve(required_size);
        vec.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();
        return (int)vec.size() == required_size;
    }
    else
    {
        file.close();
        return false;
    }
}
