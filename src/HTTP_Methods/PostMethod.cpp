#include "PostMethod.h"

// constructor for PostMethod
PostMethod::PostMethod() {}

// executes the POST method: adds a URL to the BloomFilter and saves the updated filter
// returns "201 Created" to indicate success
string PostMethod::execute(string url) {
    int sent_bytes;

    BloomFilter::getInstance().add(url);
    BloomFilter::getInstance().saveToFile("data/bloom.dat");

    return "201 Created\n";
}
