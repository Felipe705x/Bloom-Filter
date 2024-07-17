#pragma once

#include "bloom_filter.hpp"

class Data {
    private:
        std::ifstream file;
        BloomFilter bloom_filter;
        // Search a key (without using bloom filter) and returns true if its found
        bool search_grep_single(const std::string &key);
        // Search a sequence of keys (without using bloom filter)
        void search_grep(const Sequence &seq);
    public:
        // Inserts the first N*p elements of a sequence of keys
        void insert_bloom(const Sequence &seq);
        // Search a sequence of keys (using bloom filter)
        // @returns amount of false-positives
        uint64_t search_bloom(const Sequence &seq);
        // Searches a sequence of keys using both methods: with and without bloom filter
        // @returns `Result` instance that contains the time taken by both methods and the false-positive rate of the bloom method
        Result bloom_performance_test(const Sequence &seq);
        // Prints state of bloom filter
        void print_bloom_filter();
        // Constructor
        // @param `filename` path for the data source
        // @param `M` array size of the bloom filter
        // @param `K` amount of hash functions
        Data(const std::string &filename, uint64_t M, uint64_t K) : file(filename), bloom_filter(M, K) {
            if (!file.is_open())
                throw std::runtime_error("Failed to open file: " + filename);
        }
        // Destructor
        ~Data() {
            if (file.is_open())
                file.close();
        }
};

// Given an element x that was NOT inserted in the bloom filter, returns the probability of a false positive upon searching x through the filter.
// @param n amount of DISTINCT elements inserted in the filter
// @param m size of the bloom filter array
// @param k amount of hash functions used by the filter
// @note if the probability that x was not inserted in the bloom filter is 0, then this function is invalid
inline double theoretical_error(uint64_t n, uint64_t m, uint64_t k) {
    return pow(1.0 - pow((1.0 - 1.0/m),k*n), k)*100.0;
}