#include "../include/bloom_filter.hpp"
using namespace std;

int main() {
    BloomFilter bloom_filter(10, 3);
    bloom_filter.insert("me estan pegando");
    bloom_filter.insert("papito");
    cout << bloom_filter.search("papito") << endl;
    cout << bloom_filter;
    vector<string> vec = vectorizeCSV("data/Popular-Baby-Names-Final.csv");
    vector<string> vec2 = reservoirSampling(10, vec);
    for (const string &nme : vec2)
        cout << nme << endl;;
    return 0;
}