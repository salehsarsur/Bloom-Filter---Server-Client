#include "IHashFunction.h"

//implements basic std::hash function
class StdHashFunction : public IHashFunction {
private:
    hash<string> m_hash;
public:
    size_t hash_f(string string) override;
};