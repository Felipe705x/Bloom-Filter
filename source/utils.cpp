#include "../include/utils.hpp"
using namespace std;



ostream& operator<<(ostream &os, const Sequence &seq) {
    os << "[ ";
    for (uint64_t i = 0; i < seq.data.size() - 1; i++)
        os << seq.data[i] << ", ";
    os << seq.data.back() << " ]";
    return os;
}

vector<string> vectorizeCSV(string filename) {
    // Open CSV file
    ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + filename);
    // Vectorized CSV contents
    vector<string> vec;
    // String to hold a line from the file
    string line;
    
    std::getline(file, line, '\n');  //skip headers
    // Read file line by line
    while (getline(file, line, '\n'))
        vec.push_back(line);
    
    file.close();
    return vec;
}

vector<string> reservoirSampling(uint64_t k, vector<string> S, optional<uint32_t> seed) {
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

Sequence generate_sequence(uint64_t N, double p, optional<uint32_t> seed) {
    if (!seed.has_value()) {
        random_device rd;
        seed = rd();
    }
    uint64_t member_size = round(N*p);
    uint64_t outsider_size = N - member_size;
    Sequence seq;
    seq.p = p;
    seq.data = move(reservoirSampling(member_size, vectorizeCSV("data/Popular-Baby-Names-Final.csv"), seed));
    seq.data.reserve(N);
    vector<string> outsider_sample = reservoirSampling(outsider_size, vectorizeCSV("data/Film-Names.csv"), seed);
    // Insert (without copying) the elements outside the set into the sequence
    seq.data.insert(seq.data.end(), make_move_iterator(outsider_sample.begin()), make_move_iterator(outsider_sample.end()));
    return seq;
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