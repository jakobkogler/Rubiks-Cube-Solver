#pragma once

#include <vector>
#include <cstdint>
#include <fstream>

template <typename T>
class Nibble
{
public:
    Nibble(unsigned int size = 0, int default_value = 0);
    int operator[](int idx) const;
    void set(int idx, int value);
    bool read(std::string file_path);
    void store(std::string file_path);
private:
    std::vector<T> data;
    unsigned int size;
    unsigned int log;
    unsigned int mask;
    unsigned int actual_size;
};

template <typename T>
Nibble<T>::Nibble(unsigned int size, int default_value) : size(size) {
    T value = default_value & static_cast<T>(15);
    log = 0;
    for (auto shift = 4u; shift < sizeof(T) * 8; shift <<= 1) {
        value |= value << shift;
        log++;
    }
    mask = (1 << log) - 1;
    int values_per_entry = 1 << log;
    actual_size = (size + values_per_entry - 1) / values_per_entry;
    data.assign(actual_size, value);
}

template <typename T>
int Nibble<T>::operator[](int idx) const {
    T const& entry = data[idx >> log];
    int offset = (idx & mask) << 2;
    return (entry >> offset) & static_cast<T>(15);
}

template <typename T>
void Nibble<T>::set(int idx, int value) {
    T & entry = data[idx >> log];
    int offset = (idx & mask) << 2;
    entry &= ~(static_cast<T>(15) << offset);
    entry |= (value & static_cast<T>(15)) << offset;
}

template <typename T>
bool Nibble<T>::read(std::string path) {
    std::ifstream file(path.c_str(), std::ios::binary);
    if (file.good())
    {
        file.seekg(0, std::ios_base::end);
        std::size_t file_size = file.tellg();
        if (file_size == actual_size * sizeof(T)) {
            file.seekg(0, std::ios_base::beg);
            file.read(reinterpret_cast<char*>(data.data()), file_size);
        }
        file.close();
        return file_size == actual_size * sizeof(T);
    } else {
        file.close();
        return false;
    }
}

template <typename T>
void Nibble<T>::store(std::string path) {
    std::ofstream file(path.c_str(), std::ios::out | std::ofstream::binary);
    file.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(T));
    file.close();
}

using Nibble32 = Nibble<uint_fast32_t>;
