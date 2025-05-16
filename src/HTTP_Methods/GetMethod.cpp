#include "GetMethod.h"

// constructor for GetMethod
GetMethod::GetMethod() {}

// executes the GET method: checks if a URL is possibly in the BloomFilter
// returns "200 Ok" followed by "true true", "true false", or "false"
string GetMethod::execute(string url) {
    int sent_bytes;
    const char* Get = "200 Ok\n\n";
    
    string answer = (BloomFilter::getInstance().possiblyContains(url)
        ? "true " + string(BloomFilter::getInstance().isFalsePositive(url) ? "true\n" : "false\n")
        : "false\n");
    string response = string(Get) + answer;
    return response;
}
