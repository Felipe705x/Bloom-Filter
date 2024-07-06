#pragma once

#include "utils.hpp"


class BloomFilter {
    private:
        uint64_t M;
        bool *array;
        uint64_t k;
        MurmurHashInstance *hash_funcs;
    
    public:
        // Insertion method
        void insert(const std::string &key);
        // Search method: returns true if the key probably exists and false if it doesn't exist
        bool search(const std::string &key);
        // Constructor
        BloomFilter(uint64_t M, uint64_t k) : M(M), k(k) {
            array = new bool[M]();
            hash_funcs = new MurmurHashInstance[k]();
            std::random_device rd;
            // Well distributed random number generator:
            std::mt19937 rng(rd());
            std::uniform_int_distribution<uint32_t> dist;

            for (uint64_t i = 0; i < k; i++) {
                uint32_t seed = dist(rng);
                hash_funcs[i] = MurmurHashInstance(M, seed);
            }
        }
        // Destructor
        ~BloomFilter() {
            delete[] array;
            delete[] hash_funcs;
        }
        // To print the filter bool array
        friend std::ostream& operator<<(std::ostream &os, const BloomFilter &bloom_filter);
};