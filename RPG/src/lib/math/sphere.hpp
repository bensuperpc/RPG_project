/*
** BENSUPERPC PROJECT, 2020
** Math
** File description:
** sphere.cpp
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "constant.hpp"

#if __cplusplus == 202002L
#    include <numbers>
#endif

namespace sphere
{
template <typename T> T sphereSurface(const T &r);
template <typename T> T sphereVolume(const T &r);

#if CMAKE_CXX_EXTENSIONS == 1
template <typename T> T sphereSurface_Q(const T &r);
template <typename T> T sphereVolume_Q(const T &r);
#endif

} // namespace sphere
#include "sphere_imp.hpp"

#endif
