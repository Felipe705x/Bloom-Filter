#include "../include/data_search.hpp"
using namespace std;

bool Data::search_grep_single(const string &key) {
    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line == key) {   // Found match
            found = true;
            break;
        }
    }
    file.clear(); // Clear any error flags that might have been set
    file.seekg(0, ios::beg); // Go to the beggining of the file
    return found;
}

void Data::search_grep(const Sequence &seq) {
    // For every word to search
    for (const string &word : seq.data) {
        string line;
        // Search every line until word is found
        while (getline(file, line))
            if (line == word)  // Found match
                break;
        // Reset file stream for the next word
        file.clear();
        file.seekg(0, ios::beg);
    }
}

void Data::insert_bloom(const Sequence &seq) {
    uint64_t set_size = round(seq.data.size()*seq.p);
    for (uint64_t i = 0; i < set_size; i++)
        bloom_filter.insert(seq.data[i]);
}

uint64_t Data::search_bloom(const Sequence &seq) {
    uint64_t false_positives = 0;
    for (const string &word : seq.data) {
        if (bloom_filter.search(word)) {
            if(!search_grep_single(word))
                false_positives++;
        }
    }
    return false_positives;
}

Result Data::bloom_performance_test(const Sequence &seq) {
    Result res;
    auto start = std::chrono::high_resolution_clock::now();
    uint64_t fpositives = search_bloom(seq);
    auto end = std::chrono::high_resolution_clock::now();
    res.time_bloom = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    start = std::chrono::high_resolution_clock::now();
    search_grep(seq);
    end = std::chrono::high_resolution_clock::now();
    res.time_grep = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    // Amount of searched elements that do not belong to the target set
    uint64_t outsider_size = seq.data.size() - static_cast<uint64_t>(round(seq.data.size()*seq.p));
    if (outsider_size == 0)
        res.err = 0.0;
    else
        res.err = ((fpositives/static_cast<double>(outsider_size)))*100.0;
    return res;
}

void Data::print_bloom_filter() {
    cout << bloom_filter;
}