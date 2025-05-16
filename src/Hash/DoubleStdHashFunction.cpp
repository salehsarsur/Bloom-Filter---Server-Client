#include "DoubleStdHashFunction.h"

//implements basic double std::hash function
size_t DoubleStdHashFunction::hash_f(string string) {
    return m_hash(to_string(m_hash(string)));
}