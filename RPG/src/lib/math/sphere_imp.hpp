/*
** BENSUPERPC PROJECT, 2020
** Math
** File description:
** sphere.hpp
*/

#include "sphere.hpp"
template <typename T> T sphere::sphereVolume(const T &r)
{
    return (4.0 / 3.0) * PI * (r * r * r);
}
template <typename T> T sphere::sphereSurface(const T &r)
{
    return 4.0 * PI * r;
}

#if __cplusplus < 202002L
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wpedantic"
#    if CMAKE_CXX_EXTENSIONS == 1
template <typename T> T sphere::sphereVolume_Q(const T &r)
{
    return (4.0 / 3.0) * Q_PI * (r * r * r);
}
template <typename T> T sphere::sphereSurface_Q(const T &r)
{
    return 4.0 * Q_PI * r;
}
#    endif
#    pragma GCC diagnostic pop
#else
template <typename T> T sphere::sphereVolume_Q(const T &r)
{
    return (4.0 / 3.0) * std::numbers::pi * (r * r * r);
}
template <typename T> T sphere::sphereSurface_Q(const T &r)
{
    return 4.0 * std::numbers::pi * r;
}
#endif
