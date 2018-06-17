#ifndef READ_STORE
#define READ_STORE

#include <vector>
#include <string>

namespace FileIO
{
    void store_char_vector(std::vector<char> &vec, std::string path);
    bool read_char_vector(std::vector<char> &vec, std::string path, int required_size);
};

#endif // READ_STORE
