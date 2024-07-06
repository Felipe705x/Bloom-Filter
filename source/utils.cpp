#include "../include/utils.hpp"
using namespace std;


vector<string> vectorizeCSV(string filename) {
    // Open CSV file
    ifstream file(filename);
    // Vectorized CSV contents
    vector<string> vec;
    // String to hold a line from the file
    string line;
    
    std::getline(file, line);  //skip headers
    // Read file line by line
    while (getline(file, line, '\n'))
        vec.push_back(line);
    
    file.close();
    return vec;
}

vector<string> reservoirSampling(uint64_t k, vector<string> &S, optional<uint32_t> seed) {
    vector<string> reservoir(k);
    mt19937 rng;  // random number generator
    if (seed.has_value())
        rng.seed(seed.value());
    else {
        random_device rd;
        rng.seed(rd());  // random seed
    }
    for (uint64_t i = 0; i < k; i++)
        reservoir[i] = S[i];
    for (uint64_t i = k; i < S.size(); i++) {
        uniform_int_distribution<uint64_t> dist(0, i);
        uint64_t j = dist(rng);
        if (j < k)
            reservoir[j] = S[i];
    }
    return reservoir;
}

vector<pair<string, bool>> generate_sample(uint64_t N, double p) {
    
}

uint64_t MurmurHashInstance::hash(const std::string &key) const {
    uint64_t hashOut[2];
    MurmurHash3_x64_128(key.c_str(), key.length(), seed, hashOut);
    // Calculate modulo without overflow (using modulo distributive property)
    return ((hashOut[0] % M) + (hashOut[1] % M)) % M;
}

uint32_t MurmurHashInstance::getSeed() const {
    return seed;
}