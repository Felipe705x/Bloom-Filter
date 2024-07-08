#pragma once

#include <functional>
#include <string>
#include <vector>
#include <cstdint>
#include <random>
#include <iostream>
#include <optional>
#include <fstream>
#include <chrono>
#include "MurmurHash3.h"

// Stores percentage of false positives from a bloom filter search for a sequence of keys.
// Stores times taken by a search with and without bloom filter for a sequence of keys.
class Result {
    public:
        double err;
        long long time_grep;
        long long time_bloom;
};

// Represents a sequence N of |N| keys
// A fraction `p` of the elements belong to a particular set.
class Sequence {
    public:
        double p;
        std::vector<std::string> data;
        // To print sequence
        friend std::ostream& operator<<(std::ostream &os, const Sequence &seq);
};

// Transforms CSV contents into a vector
std::vector<std::string> vectorizeCSV(std::string filename);


// Returns a uniform random sample of size k given a vector of strings S (using "Reservoir Sampling")
std::vector<std::string> reservoirSampling(uint64_t k, std::vector<std::string> S, std::optional<uint32_t> seed = std::nullopt);

// Generates a random sequence N of size n where p is the fraction of elements in N that belong to our target dataset.
// @returns `Sequence` instance that consists of two vectors: one for the N*p members of the set, and one for the rest
Sequence generate_sequence(uint64_t N, double p, std::optional<uint32_t> seed = std::nullopt);

// Encapsulates a murmurHash instance with a given seed and array size
class MurmurHashInstance {
    private:
        uint64_t M;
        uint32_t seed;
    public:
        // Default constructor for array initilization
        MurmurHashInstance() : M(1), seed(0) {}
        // Constructor for intended use
        MurmurHashInstance(uint64_t M, uint32_t seed) : M(M), seed(seed) {}
        // Hash method
        uint64_t hash(const std::string &key) const;
        // Get seed used for instance
        uint32_t getSeed() const;
};