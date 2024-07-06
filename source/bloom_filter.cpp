#include "../include/bloom_filter.hpp"
using namespace std;

ostream& operator<<(ostream &os, const BloomFilter &bloom_filter) {
    os << "[ ";
    for (uint64_t i = 0; i < bloom_filter.M; i++) {
        os << static_cast<int>(bloom_filter.array[i]) << " ";
    }
    os << "]";
    return os;
}

void BloomFilter::insert(const std::string &key) {
    for (uint64_t i = 0; i < k; i++)
        array[hash_funcs[i].hash(key)] = 1;
}

bool BloomFilter::search(const std::string &key) {
    for (uint64_t i = 0; i < k; i++) {
        if (array[hash_funcs[i].hash(key)] == 0)
            return false;
    }
    return true;
}