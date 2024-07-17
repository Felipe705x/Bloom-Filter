#include "../include/data_search.hpp"
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    vector<uint64_t> N_values = {pow(2, 10), pow(2, 12), pow(2, 14), pow(2, 16)};
    vector<double> p_values = {0, 0.25, 0.5, 0.75, 1};

    for (uint64_t N : N_values) {
        for (double p : p_values) {
            uint64_t M = pow(2, 14);
            uint64_t n = round(N * p);
            uint64_t K = max(static_cast<uint64_t>(1), static_cast<uint64_t>(round((static_cast<double>(M) / n) * log(2))));

            Data data("data/Popular-Baby-Names-Final.csv", M, K);
            Sequence seq = generate_sequence(N, p);
            data.insert_bloom(seq);

            Result res = data.bloom_performance_test(seq);

            cout << "N: " << N << ", p: " << p << endl;
            cout << "Search with bloom filter: " << res.time_bloom << " ns" << endl;
            cout << "Search with grep: " << res.time_grep << " ns" << endl;
            cout << "Bloom error rate: " << res.err << "%" << endl;
            cout << "Theoretical bloom error rate: " << pow(1.0 - pow((1.0 - 1.0 / M), K * n), K) * 100.0 << "%" << endl;
            cout << "Using bloom filter results in a X" << res.time_grep / static_cast<double>(res.time_bloom) << " speedup" << endl;
            cout << endl;
        }
    }

    return 0;
}
