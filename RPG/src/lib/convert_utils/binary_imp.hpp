/*
** BENSUPERPC PROJECT, 2020
** RPG
** Source: https://stackoverflow.com/questions/32410186/convert-bool-array-to-int32-unsigned-int-and-double
** binary_imp.hpp
*/

#include "binary.hpp"

template <typename T> T binary::bitArrayToInt_big(bool ar[], size_t ar_size)
{
    T ret {};

    for (size_t i = 0; i < ar_size; ++i) {
        T s {ar[i]};
        s <<= i;
        ret |= s;
    }

    return ret;
}