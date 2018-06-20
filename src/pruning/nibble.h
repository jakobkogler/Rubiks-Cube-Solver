#pragma once

#include <vector>
#include <cstdint>
#include <fstream>

template <typename T>
class Nibble
{
public:
    Nibble(uint64_t size = 0, int default_value = 0);
    int get(uint32_t idx) const;
    int get(std::pair<uint32_t, uint32_t> idx) const;
    void set(uint32_t idx, int value);
    void set(std::pair<uint32_t, uint32_t> idx, int value);
    uint64_t size() const;
    bool read(std::string file_path);
    void store(std::string file_path);
private:
    std::vector<T> data;
    uint64_t elements;
    unsigned int log;
    unsigned int mask;
    uint64_t actual_size;
};

template <typename T>
Nibble<T>::Nibble(uint64_t size, int default_value) : elements(size) {
    T value = default_value & static_cast<T>(15);
    log = 0;
    for (auto shift = 4u; shift < sizeof(T) * 8; shift <<= 1) {
        value |= value << shift;
        log++;
    }
    mask = (1 << log) - 1;
    int values_per_entry = 1 << log;
    actual_size = (elements + values_per_entry - 1) / values_per_entry;
    data.assign(actual_size, value);
}

template <typename T>
int Nibble<T>::get(uint32_t idx) const {
    T const& entry = data[idx >> log];
    int offset = (idx & mask) << 2;
    return (entry >> offset) & static_cast<T>(15);
}

template <typename T>
int Nibble<T>::get(std::pair<uint32_t, uint32_t> idx) const {
    T const& entry = data[idx.first];
    idx.second <<= 2;
    return (entry >> idx.second) & static_cast<T>(15);
}

template <typename T>
void Nibble<T>::set(uint32_t idx, int value) {
    T & entry = data[idx >> log];
    int offset = (idx & mask) << 2;
    entry &= ~(static_cast<T>(15) << offset);
    entry |= (value & static_cast<T>(15)) << offset;
}

template <typename T>
void Nibble<T>::set(std::pair<uint32_t, uint32_t> idx, int value) {
    T & entry = data[idx.first];
    idx.second <<= 2;
    entry &= ~(static_cast<T>(15) << idx.second);
    entry |= (value & static_cast<T>(15)) << idx.second;
}

template <typename T>
uint64_t Nibble<T>::size() const {
    return elements;
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

using Nibble32 = Nibble<uint32_t>;
