/*
** BENSUPERPC PROJECT, 2020
** Math
** F
** prime.cpp
*/

#ifndef PRIME_HPP_
#define PRIME_HPP_

#include <cmath>

namespace math
{

namespace prime
{
bool isPrime_opti_0(const long long int &);
bool isPrime_opti_1(const long long int &);
bool isPrime_opti_2(const long long int &);
bool isPrime_opti_3(const long long int &);
bool isPrime_opti_4(const long long int &);

bool isPrime_opti_5(const long long int &);
inline long long int PowerMod(long long int, long long int, long long int);
inline long long int MultiplyMod(long long int, long long int, long long int);

bool isPrime_opti_6(const long long int &);
bool isPrime_opti_7(const long long int &);
} // namespace prime
} // namespace math

// THANK https://www.geeksforgeeks.org/c-program-to-check-prime-number/
// THANK https://stackoverflow.com/questions/4424374/determining-if-a-number-is-prime
#endif
