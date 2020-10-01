/*
** BENSUPERPC PROJECT, 2020
** CPU
** File description:
** vector.cpp
*/

#include "vector_avx.hpp"

#ifdef __AVX2__
#pragma GCC push_options
#pragma GCC optimize ("-O1")
__m256 my::vector_avx::HorizontalSums(__m256 &v0, __m256 &v1, __m256 &v2, __m256 &v3, __m256 &v4, __m256 &v5, __m256 &v6, __m256 &v7)
{
    const __m256 &&s01 = _mm256_hadd_ps(v0, v1);
    const __m256 &&s23 = _mm256_hadd_ps(v2, v3);
    const __m256 &&s45 = _mm256_hadd_ps(v4, v5);
    const __m256 &&s67 = _mm256_hadd_ps(v6, v7);
    const __m256 &&s0123 = _mm256_hadd_ps(s01, s23);
    const __m256 &&s4556 = _mm256_hadd_ps(s45, s67);

    // inter-lane shuffle
    v0 = _mm256_blend_ps(s0123, s4556, 0xF0);
    v1 = _mm256_permute2f128_ps(s0123, s4556, 0x21);

    return _mm256_add_ps(v0, v1);
}

inline __m256 my::vector_avx::sort_of_alternative_hadd_ps(__m256 &x, __m256 &y)
{
    __m256 y_hi_x_lo = _mm256_blend_ps(x, y, 0b11001100);      /* y7 y6 x5 x4 y3 y2 x1 x0 */
    __m256 y_lo_x_hi = _mm256_shuffle_ps(x, y, 0b01001110);    /* y5 y4 x7 x6 y1 y0 x3 x2 */
    return _mm256_add_ps(y_hi_x_lo, y_lo_x_hi);
}

__m256 my::vector_avx::HorizontalSums_less_p5_pressure(__m256 &v0, __m256 &v1, __m256 &v2, __m256 &v3, __m256 &v4, __m256 &v5, __m256 &v6, __m256 &v7)
{
    __m256 &&s01 = sort_of_alternative_hadd_ps(v0, v1);
    __m256 &&s23 = sort_of_alternative_hadd_ps(v2, v3);
    __m256 &&s45 = sort_of_alternative_hadd_ps(v4, v5);
    __m256 &&s67 = sort_of_alternative_hadd_ps(v6, v7);
    __m256 &&s0123 = _mm256_hadd_ps(s01, s23);
    __m256 &&s4556 = _mm256_hadd_ps(s45, s67);

    v0 = _mm256_blend_ps(s0123, s4556, 0xF0);
    v1 = _mm256_permute2f128_ps(s0123, s4556, 0x21);
    return _mm256_add_ps(v0, v1);
}
#pragma GCC pop_options

inline double my::vector_avx::hsum_double_avx(__m256d &v) {
    __m128d &&vlow  = _mm256_castpd256_pd128(v);
    __m128d &&vhigh = _mm256_extractf128_pd(v, 1);
            vlow  = _mm_add_pd(vlow, vhigh);
    __m128d &&high64 = _mm_unpackhi_pd(vlow, vlow);
    return  _mm_cvtsd_f64(_mm_add_sd(vlow, high64));
}

inline float my::vector_avx::hsum_float_avx(__m256 &v) {
    const __m128 &&x128 = _mm_add_ps(_mm256_extractf128_ps(v, 1), _mm256_castps256_ps128(v));
    const __m128 &&x64 = _mm_add_ps(x128, _mm_movehl_ps(x128, x128));
    const __m128 &&x32 = _mm_add_ss(x64, _mm_shuffle_ps(x64, x64, 0x55));
    return _mm_cvtss_f32(x32);
}

inline void my::vector_avx::multiply_and_add(__m256 &a, __m256 &b, __m256 &c, __m256 &d) {
  d = _mm256_fmadd_ps(a, b, c);
}

inline float my::vector_avx::extract_float(const __m128 &v, const int i)
{
    float x = 0.0;
    _MM_EXTRACT_FLOAT(x, v, i);
    return x;
}

inline float* my::vector_avx::__m128_to_float(const __m128 &v)
{
    return (float*)&v;
}

inline float* my::vector_avx::__m256_to_float(const __m256 &v)
{
    return (float*)&v;
}

inline double* my::vector_avx::__m128_to_double(const __m128d &v)
{
    return (double*)&v;
}

inline double* my::vector_avx::__m256_to_double(const __m256d &v)
{
    return (double*)&v;
}

inline int* my::vector_avx::__m128_to_integer(const __m128i &v)
{
    return (int*)&v;
}

inline int* my::vector_avx::__m256_to_integer(const __m256i &v)
{
    return (int*)&v;
}


#endif