#ifndef IHTTPMethods_H 
#define IHTTPMethods_H

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "BloomFilter.h"
using namespace std;

// IHTTPMethods is an abstract base class for HTTP methods (GET, POST, DELETE, etc.)
// it provides a pure virtual function `execute` that each method (e.g., GetMethod, PostMethod) must implement

class IHTTPMethods {
public:
    // pure virtual function for executing HTTP methods
    virtual string execute(string url) = 0;
};

#endif
