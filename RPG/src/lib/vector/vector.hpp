/*
** BENSUPERPC PROJECT, 2020
** Math
** Source: https://stackoverflow.com/questions/178265/what-is-the-most-hard-to-understand-piece-of-c-code-you-know https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
** vector.hpp
*/

#ifndef VECTOR_HPP_
#    define VECTOR_HPP_

#    include <algorithm>
#    include <iomanip>
#    include <iostream>
#    include <random>
#    include <vector>

namespace vector
{
std::vector<std::vector<int>> generate_matrix(size_t, size_t);
std::vector<std::vector<int>> generate_matrix(size_t, size_t, int);
void print_2d(std::vector<std::vector<int>> &);
void fill_row(std::vector<int> &);
void fill_rowull(std::vector<uint64_t> &);

void fill_matrix_1(std::vector<std::vector<int>> &);
void fill_matrix_2(std::vector<std::vector<int>> &);
void fill_matrix_2(std::vector<std::vector<int>> &, int, int);

void cache_unfriendly_copy(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &);
void cache_friendly_copy(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &);

template <typename T> double everage(const T &vec);

#    include "vector_imp.hpp"

} // namespace vector
#endif
// https://stackoverflow.com/questions/22312959/how-to-fill-a-vector-with-a-range
/*
auto && Mat = vector::generate_matrix(10000, 10000, 0);
auto && Mat2 = vector::generate_matrix(10000, 10000, 5);
t1 = chrono::now();
Mat = Mat2;
t2 = chrono::now();
std::cout << chrono::duration(t1, t2).count() << std::endl;

t1 = chrono::now();
std::copy(Mat.begin(), Mat.end(), std::back_inserter(Mat2));
t2 = chrono::now();
std::cout << chrono::duration(t1, t2).count() << std::endl;

t1 = chrono::now();
Mat2.assign(Mat.begin(), Mat.end());
t2 = chrono::now();
std::cout << chrono::duration(t1, t2).count() << std::endl;
*/