#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include "IHashFunction.h"

// the BloomFilter class provides a probabilistic data structure to check for membership
// it uses multiple hash functions and a bit vector for space-efficient storage
// false positives are possible; false negatives are not

class BloomFilter {
private:
    int size; // size of the bit array
    vector<IHashFunction*> hashFunctions; // list of hash functions used
    vector<bool> bits; // bit vector for Bloom filter
    unordered_set<string> realBlacklist; // actual set to detect false positives
    static BloomFilter* instance; // singleton instance pointer
    BloomFilter(int size, vector<IHashFunction*> hashFunctions); // private constructor

public:
    BloomFilter(const BloomFilter&) = delete; // disable copy constructor
    BloomFilter& operator=(const BloomFilter&) = delete; // disable assignment operator

    static void initBloomFilter(int size, vector<IHashFunction*> hashFunctions); // initializes the singleton
    static BloomFilter& getInstance(); // returns singleton reference

    void updateBits(string url); // function to update bits vector with a URL
    void add(string url); // add the url to the blacklist and updates the bloom filter 
    bool possiblyContains(string url); // checks if the url may be in the list
    bool isFalsePositive(string url); // false positive checking
    void saveToFile(string filename); // saving a bloomfilter into a file
    void loadBlacklistFromFile(string filename); //loading the urls form blacklist file
    bool deleteFromBlacklist(string url, string filename); //deleting the url only form blacklist file
};
#endif