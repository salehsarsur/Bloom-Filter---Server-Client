#ifndef POSTMETHOD_H
#define POSTMETHOD_H

#include "IHTTPMethods.h"

// PostMethod handles the HTTP POST operation
// it adds a URL to the BloomFilter and saves the updated filter to a file

class PostMethod : public IHTTPMethods {
public:
    PostMethod(); // constructor
    string execute(string url); // executes the POST method and returns the result
};

#endif
