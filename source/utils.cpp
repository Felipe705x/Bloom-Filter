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
        throw runtime_error("Failed to open file: " + filename);
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


vector<string> repSampling(uint64_t k, vector<string> &S, optional<uint32_t> seed) {
    vector<string> sample;
    sample.reserve(k);
    mt19937 rng;  // random number generator
    if (seed.has_value())
        rng.seed(seed.value());
    else {
        random_device rd;
        rng.seed(rd());  // random seed
    }
    uniform_int_distribution<uint64_t> dist(0, S.size() - 1);
    for (uint64_t i = 0; i < k; i++)
        sample.push_back(S[dist(rng)]);
    return sample;
}

vector<string> reservoirSampling(uint64_t k, string filename, optional<uint32_t> seed) {
    vector<string> reservoir(k);
    mt19937 rng;  // random number generator
    if (seed.has_value())
        rng.seed(seed.value());
    else {
        random_device rd;
        rng.seed(rd());  // random seed
    }
    ifstream file(filename);
    if (!file.is_open())
        throw runtime_error("Failed to open file: " + filename);
    string line;
    uint64_t i = 0;
    while(i < k && getline(file, line)) {
        reservoir[i] = line;
        i++;
    }
    if (i < k)
        throw runtime_error("File contains fewer than k lines");
    while (getline(file, line)) {
        uniform_int_distribution<uint64_t> dist(0, i);
        uint64_t j = dist(rng);
        if (j < k)
            reservoir[j] = line;
        i++;
    }
    file.close();
    return reservoir;
}


Sequence generate_sequence(uint64_t N, double p, std::vector<std::string> &fake_data, optional<uint32_t> seed) {
    if (!seed.has_value()) {
        random_device rd;
        seed = rd();
    }
    uint64_t member_size = round(N*p);
    uint64_t outsider_size = N - member_size;
    Sequence seq;
    seq.p = p;
    seq.data = move(reservoirSampling(member_size,"data/Popular-Baby-Names-Final.csv", seed));
    seq.data.reserve(N);
    vector<string> outsider_sample = repSampling(outsider_size, fake_data, seed);
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