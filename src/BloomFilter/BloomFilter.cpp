#include "BloomFilter.h"

// static instance pointer initialization
BloomFilter* BloomFilter::instance = nullptr;

// constructor for BloomFilter: initializes size, hash functions, and bit vector
BloomFilter::BloomFilter(int size, vector<IHashFunction*> hashFunctions)
    : size(size), hashFunctions(hashFunctions), bits(size, false) {}

// initializes the singleton instance if it doesn't exist
void BloomFilter::initBloomFilter(int size, vector<IHashFunction*> hashFunctions) {
    if (!instance) {
        instance = new BloomFilter(size, hashFunctions);
    }
}

// returns a reference to the singleton BloomFilter instance
BloomFilter& BloomFilter::getInstance() {
    if (!instance) {
        exit(EXIT_FAILURE);
    }
    return *instance;
}

// updates bit vector based on URL's hash values and adds to real blacklist
void BloomFilter::updateBits(string url){
    for (IHashFunction* hashFunc : hashFunctions) {
        size_t index = ((hashFunc->hash_f(url)) % size);
        bits[index] = true;
    }
    realBlacklist.insert(url);
}

// adds a URL to the BloomFilter and saves it to the blacklist file
void BloomFilter::add(string url) {
    ofstream file("data/blacklist.txt", ios::app);
    if (!file.is_open()) return;
    updateBits(url);
    file << url << "\n";
    file.close();
}

// checks if a URL might exist in the BloomFilter (may be false positive)
bool BloomFilter::possiblyContains(string url) {
    for (IHashFunction* hashFunc : hashFunctions) {
        size_t index = hashFunc->hash_f(url) % size;
        if (!bits[index]) return false;
    }
    return true;
}

// checks if a URL is a false positive
bool BloomFilter::isFalsePositive(string url) {
    return possiblyContains(url) && (realBlacklist.find(url) != realBlacklist.end());
}

// saves the BloomFilter bit vector to a file
void BloomFilter::saveToFile(string filename){
    ofstream file(filename);
    if (!file.is_open()) return;
    file << size << '\n';
    for (int i = 0; i < size; ++i)
        file << (bits[i] ? '1' : '0');
    file.close();
}

// loads URLs from a file and updates the BloomFilter
void BloomFilter::loadBlacklistFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    string url;
    while (getline(file, url))
        updateBits(url);
    file.close();
}

// deletes a URL from blacklist file and in memory set (not from BloomFilter)
bool BloomFilter::deleteFromBlacklist(string url, string filename){
    ifstream file(filename);
    if (!file.is_open()) return false;
    vector<string> lines;
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line == url) {
            found = true;
            if(realBlacklist.find(url) != realBlacklist.end())
                realBlacklist.erase(url);
            continue;
        }
        lines.push_back(line);
    }
    file.close();
    if (!found) return false;
    ofstream ofile(filename, ios::trunc);
    for (const string& l : lines) {
        ofile << l << '\n';
    }
    return true;
}
