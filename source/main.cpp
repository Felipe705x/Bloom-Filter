#include "../include/data_search.hpp"
using namespace std;

int main() {
    double p = 1.0/2.0;
    uint64_t N = pow(2, 13);
    // Elements inserted in bloom filter:
    uint64_t n = round(N*p);
    //uint64_t M = pow(2, 14);
    uint64_t M = round(-(n*log(0.01))/(log(2)*log(2)));
    if (M == 0)
        M = 1;
    // Elements that wont be inserted:
    vector<string> fake_data = vectorizeCSV("data/Film-Names.csv");

    // Optimal K value (for minimizing error)
    uint64_t K;
    // Edge case (1): No elements inserted
    if (n == 0)
        K = static_cast<uint64_t>(1);
    else
        K = max(static_cast<uint64_t>(1), static_cast<uint64_t>(round((static_cast<double>(M/n))*log(2))));

    double theoretical_err;
    // Edge case (2): Only elements that were inserted will be searched
    if (N == n)  // usual formula becomes invalid, as the pre-condition (i.e. "given we search x not inserted") becomes impossible to satisfy
        theoretical_err = 0;
    else
        theoretical_err = theoretical_error(n, M, K); // usual formula
    // Experiment
    Data data("data/Popular-Baby-Names-Final.csv", M, K);
    Sequence seq = generate_sequence(N, p, fake_data);
    data.insert_bloom(seq);
    Result res = data.bloom_performance_test(seq);
    cout << "Search with bloom filter: " << res.time_bloom << " ns" << endl;
    cout << "Search with grep: " << res.time_grep << " ns" << endl;
    cout << "Bloom error rate: " << res.err << "%" << endl;
    cout << "Theoretical bloom error rate: " << theoretical_err << "%" << endl;
    cout << endl;
    cout << "Using bloom filter results in a X" << res.time_grep/static_cast<double>(res.time_bloom) << " speedup" << endl;
    //data.print_bloom_filter();
    return 0;
}