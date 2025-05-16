#include <iostream>
#include <functional>
using namespace std;

#ifndef IHASH_H 
#define IHASH_H

// abstract hashfunction interface
class IHashFunction {
public:
    virtual size_t  hash_f(string string) = 0;
    virtual ~IHashFunction() = default;
protected:
    hash<string> m_hash;
};
#endif