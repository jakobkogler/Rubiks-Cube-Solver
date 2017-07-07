#ifndef READ_STORE
#define READ_STORE

#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <unordered_map>

using namespace std;

namespace FileIO
{
    void store_char_vector(vector<char> &vec, string path);
    bool read_char_vector(vector<char> &vec, string path, long long required_size);
    void store_unordered_map(unordered_map<long long, char> &map, string path);
    bool read_unordered_map(unordered_map<long long, char> &map, string path, int required_size);
};

#endif // READ_STORE
