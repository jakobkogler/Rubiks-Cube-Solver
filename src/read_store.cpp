#include "read_store.h"

void Read_Store::store_char_vector(vector<char> &vec, string path)
{
	ofstream file(path.c_str(), ios::out | ofstream::binary);
	file.write(reinterpret_cast<const char *>(&vec[0]), vec.size()*sizeof(char));
	file.close();
}

bool Read_Store::read_char_vector(vector<char> &vec, string path, int required_size)
{
	ifstream file(path.c_str(), ios::binary);
	if (file.good())
	{
		vec.reserve(required_size);
		vec.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
		file.close();
		return vec.size() == required_size;
	}
	else
	{
		file.close();
		return false;
	}
}
