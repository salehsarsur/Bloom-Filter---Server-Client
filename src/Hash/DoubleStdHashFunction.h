#include "IHashFunction.h"
#include <string>

//implements basic double std::hash function
class DoubleStdHashFunction : public IHashFunction {
private:
    hash<string> m_hash;
public:
    size_t hash_f(string string) override;
};