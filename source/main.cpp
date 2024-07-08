#include "../include/data_search.hpp"
using namespace std;

int main() {
    uint64_t N = pow(2, 13);
    uint64_t M = pow(2, 14);
    double p = 1.0/2.0;
    // Elements inserted in bloom filter:
    uint64_t n = round(N*p);
    uint64_t K = max(static_cast<uint64_t>(1), static_cast<uint64_t>(round((static_cast<double>(M/n))*log(2))));
    Data data("data/Popular-Baby-Names-Final.csv", M, K);
    Sequence seq = generate_sequence(N, p);
    data.insert_bloom(seq);
    Result res = data.bloom_performance_test(seq);
    cout << "Search with bloom filter: " << res.time_bloom << " ns" << endl;
    cout << "Search with grep: " << res.time_grep << " ns" << endl;
    cout << "Bloom error rate: " << res.err << "%" << endl;
    cout << "Theoretical bloom error rate: " << pow(1.0 - pow((1.0 - 1.0/M),K*n), K)*100.0 << "%" << endl;
    cout << endl;
    cout << "Using bloom filter results in a X" << res.time_grep/static_cast<double>(res.time_bloom) << " speedup" << endl;
    //data.print_bloom_filter();
    return 0;
}