#include "fileio.h"
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

void FileIO::store_char_vector(vector<char> &vec, string path)
{
    ofstream file(path.c_str(), ios::out | ofstream::binary);
    file.write(&vec[0], vec.size()*sizeof(char));
    file.close();
}

bool FileIO::read_char_vector(vector<char> &vec, string path, int required_size)
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

bool FileIO::read_unordered_map(unordered_map<long long, char> &map, string path, int required_size) {
    map = unordered_map<long long, char>(73596790*2);
    ifstream ifile(path, ios::binary);
    if (ifile.good()) {
        boost::archive::binary_iarchive iarch(ifile);
        iarch >> map;
        ifile.close();
        return true;
    }
    ifile.close();
    return false;
}

void FileIO::store_unordered_map(unordered_map<long long, char> &map, string path) {
    ofstream ofile(path, ios::out | ofstream::binary);
    boost::archive::binary_oarchive oarch(ofile);
    oarch << map;
    ofile.close();
}
