/*
** BENSUPERPC PROJECT, 2020
** Math
** desc.
** vector_imp.hpp
*/

#include "vector.hpp"

template <typename T> double everage(const T &vec)
{
    return double(accumulate(vec.begin(), vec.end(), 0.0)) / double(vec.size());
}
