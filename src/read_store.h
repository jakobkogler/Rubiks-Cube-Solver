#ifndef READ_STORE
#define READ_STORE

#include <vector>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

namespace Read_Store
{
	void store_char_vector(vector<char> &vec, string path);
	bool read_char_vector(vector<char> &vec, string path, int required_size);
};

#endif // READ_STORE
