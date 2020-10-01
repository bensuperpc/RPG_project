/*
** BENSUPERPC PROJECT, 2020
** Math
** Source: https://stackoverflow.com/questions/178265/what-is-the-most-hard-to-understand-piece-of-c-code-you-know https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
** vector.hpp
*/

#ifndef VECTOR_AVX_HPP_
#define VECTOR_AVX_HPP_
#ifdef __AVX2__
#include <immintrin.h>

//__m256 m1 = _mm256_setr_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);

namespace my
{
namespace vector_avx
{
inline __m256 HorizontalSums(__m256 &, __m256 &, __m256 &, __m256 &, __m256 &, __m256 &, __m256 &, __m256 &);
inline __m256 HorizontalSums_less_p5_pressure(__m256 &, __m256 &, __m256 &, __m256 &, __m256 &, __m256 &, __m256 &, __m256 &);
inline __m256 sort_of_alternative_hadd_ps(__m256 &, __m256 &);

inline double hsum_double_avx(__m256d &);
inline float hsum_float_avx(__m256 &);

inline void multiply_and_add(__m256 &, __m256 &, __m256 &, __m256 &);

inline float extract_float(const __m128 &, const int i);


inline float* __m128_to_float(const __m128 &);
inline float* __m256_to_float(const __m256 &);

inline double* __m128_to_double(const __m128d &);
inline double* __m256_to_double(const __m256d &);

inline int* __m128_to_integer(const __m128i &);
inline int* __m256_to_integer(const __m256i &);


} // namespace vector_avx
} // namespace my
#endif
#endif
//https://stackoverflow.com/questions/51274287/computing-8-horizontal-sums-of-eight-avx-single-precision-floating-point-vectors
//https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=_mm_add_sd&expand=154

//_mm256_add_ps/_mm256_add_pd
//_mm256_add_epi8/16/32/64 / _mm256_add_epu8/16/32/64
//_mm256_mul_ps/_mm256_mul_pd
//_mm256_div_ps/_mm256_div_pd
//_mm256_sub_ps/_mm256_sub_pd