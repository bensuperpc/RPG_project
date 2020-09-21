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

#include "game.hpp"
//#include <iostream>

int main(int argc, char *argv[], char *envp[])
{
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
