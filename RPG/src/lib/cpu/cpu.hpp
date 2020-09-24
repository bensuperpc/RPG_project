/*
** BENSUPERPC PROJECT, 2020
** Math
** Source: https://stackoverflow.com/questions/178265/what-is-the-most-hard-to-understand-piece-of-c-code-you-know https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
** cpu.cpp
*/

#ifndef CPU_HPP_
#define CPU_HPP_

#include <iostream>
#include <string>

using namespace std;

namespace cpu
{
#pragma GCC diagnostic ignored "-Wundef"
#if (__i386__ || _M_IX86 || __x86_64__ || _M_AMD64)
void cpuID(unsigned i, unsigned regs[4]);

#endif
} // namespace cpu

// https://stackoverflow.com/questions/2901694/how-to-detect-the-number-of-physical-processors-cores-on-windows-mac-and-linu
#endif
