#ifndef READ_STORE
#define READ_STORE

#include <vector>
#include <string>

using namespace std;

namespace FileIO
{
    void store_char_vector(vector<char> &vec, string path);
    bool read_char_vector(vector<char> &vec, string path, int required_size);
};

#endif // READ_STORE
