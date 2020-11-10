/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** main.hpp
*/
// https://stackoverflow.com/questions/1505582/determining-32-vs-64-bit-in-c
// Check windows

#if _MSC_FULL_VER
#    if _WIN32 || _WIN64
#        if _WIN64
#            define ENV64BIT
#        else
#            define ENV32BIT
#        endif
#    endif
#endif

// Check GCC
#if (__GNUC__ || __clang__)
#    if (__x86_64__ || __ppc64__ || __aarch64__)
#        define ENV64BIT
#    else
#        define ENV32BIT
#    endif
#endif

// https://www.quora.com/What-are-some-macros-that-are-used-in-C++-programming-contests
#define maX(a, b) ((a) > (b) ? (a) : (b))
#define miN(a, b) ((a) < (b) ? (a) : (b))

#include <boost/math/special_functions/prime.hpp>
#include <iostream>
#include <tuple>
#include <vector>
#include "game.hpp"
#include "math/prime.hpp"
#include "time/chrono/chrono.hpp"

int main(int argc, char *argv[], char *envp[])
{
    // http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
    // https://bigprimes.org/
    /*
    const std::vector<long long int> prime_nbrs = {30000001, 40000003, 400000009, 400000009, 4000000007, 40000000003, 400000000019, 999999999989,
        67280421310721, 67428322156073819, 979025471535264563, 3815136756226794067};*/
    // 4001, 40009, 400009, 3000017, 4000037, 7720673229399130991
    /*const std::vector<std::pair<const std::string, bool (*)(const long long int &)>> pointer_map {{"isPrime_opti_0", &math::prime::isPrime_opti_0},
        {"isPrime_opti_1", &math::prime::isPrime_opti_1}, {"isPrime_opti_2", &math::prime::isPrime_opti_2}, {"isPrime_opti_3", &math::prime::isPrime_opti_3},
        {"isPrime_opti_4", &math::prime::isPrime_opti_4}, {"isPrime_opti_5", &math::prime::isPrime_opti_5}, {"isPrime_opti_6", &math::prime::isPrime_opti_6},
        {"isPrime_opti_7", &math::prime::isPrime_opti_7}};*/
    /*
    const std::vector<std::pair<const std::string, bool (*)(const long long int &)>> pointer_map {{"isPrime_opti_1", &math::prime::isPrime_opti_1},
        {"isPrime_opti_2", &math::prime::isPrime_opti_2}, {"isPrime_opti_3", &math::prime::isPrime_opti_3}, {"isPrime_opti_4", &math::prime::isPrime_opti_4},
        {"isPrime_opti_5", &math::prime::isPrime_opti_5}, {"isPrime_opti_6", &math::prime::isPrime_opti_6}};

    // 7<=0<<<<<1<

    auto &&t1 = chrono::now();
    auto &&t2 = chrono::now();

    std::vector<std::vector<long double>> time {};
    time.reserve(pointer_map.size());
    for (auto &elem_fn : pointer_map) {

        time.emplace_back(std::vector<long double>());
        time.back().reserve(prime_nbrs.size());

        for (auto &prime_nbr : prime_nbrs) {
            t1 = chrono::now();
            if ((*elem_fn.second)(prime_nbr) != true) {
                std::cout << "ERROR, is prime NBR: " << prime_nbr << " FROM: " << elem_fn.first << std::endl;
            }
            t2 = chrono::now();
            time.back().emplace_back(chrono::duration(t1, t2).count());
        }
    }
    std::cout << std::setprecision(8) << std::fixed;
    double moy = 0.0f;
    for (auto &y : time) {
        std::cout << "FN: ";
        for (auto &x : y) {
            moy = moy + x;
            std::cout << x << "s ";
        }
        std::cout << "moy:" << moy / (double)y.size() << "s";
        moy = 0.0f;
        std::cout << std::endl;
    }

    return 0;*/
    // std::cout << std::setprecision(50) << math::square_root::invsqrt(2.0) << std::endl;
    // return 0;
    // std::cout << CMAKE_CXX_COMPILER_VERSION << std::endl;
    /*
    #if defined(ENV64BIT)
        if (sizeof(void *) != 8) {
            wprintf(L"ENV64BIT: Error: pointer should be 8 bytes. Exiting.");
            exit(0);
        }
        wprintf(L"Diagnostics: we are running in 64-bit mode.\n");
    #elif defined(ENV32BIT)
        if (sizeof(void *) != 4) {
            wprintf(L"ENV32BIT: Error: pointer should be 4 bytes. Exiting.");
            exit(0);
        }
        wprintf(L"Diagnostics: we are running in 32-bit mode.\n");
    #else
    #    error "Must define either ENV32BIT or ENV64BIT".
    #endif

    #if defined(ENV64BIT)
        // 64-bit code here.
    #elif defined(ENV32BIT)
        // 32-bit code here.
    #else
    #    error "Must define either ENV32BIT or ENV64BIT"
    #endif
    */
    Game game = Game();
    game.Launch();
    return 0;
}
