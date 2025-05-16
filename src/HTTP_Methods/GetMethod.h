#ifndef GETMETHOD_H
#define GETMETHOD_H

#include "IHTTPMethods.h"

// GetMethod handles the HTTP GET operation
// it checks if a URL exists in the BloomFilter and if it's a false positive

class GetMethod : public IHTTPMethods {
public:
    GetMethod(); // constructor
    string execute(string url); // executes the GET method and returns the result
};

#endif
