#pragma once

#include <functional>
#include <string>
#include <vector>
#include <cstdint>
#include <random>
#include <iostream>
#include <optional>
#include <fstream>
#include "MurmurHash3.h"

// To encapsulate the results: Negative (N), Positive (P) and False-Positive (FP)
typedef enum Result {N, P, FP} Result;

// Transforms CSV contents into a vector
std::vector<std::string> vectorizeCSV(std::string filename);

// Returns a uniform random sample of size k given a vector of strings S (using "Reservoir Sampling")
std::vector<std::string> reservoirSampling(uint64_t k, std::vector<std::string> &S, std::optional<uint32_t> seed = std::nullopt);

// Generates a random sample N of size n where p is the fraction of elements in N that belong to our target dataset.
// @returns a vector of pairs `<string, bool>` where the first component corresponds to the element, and the second the bool value indicating if it belongs to the dataset or not
std::vector<std::pair<std::string, bool>> generate_sample(uint64_t N, double p);

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