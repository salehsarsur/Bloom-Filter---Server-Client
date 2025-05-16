#include "StdHashFunction.h"

//implements basic std::hash function
size_t StdHashFunction::hash_f(string string) {
    return m_hash(string);
}