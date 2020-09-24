/*
** BENSUPERPC PROJECT, 2020
** CPU
** File description:
** cpu.cpp
*/

#include "cpu.hpp"

#pragma GCC diagnostic ignored "-Wundef"
#if (__i386__ || _M_IX86 || __x86_64__ || _M_AMD64)
void cpu::cpuID(unsigned i, unsigned regs[4])
{
#    ifdef _WIN32
    __cpuid((int *)regs, (int)i);

#    else
    asm volatile("cpuid" : "=a"(regs[0]), "=b"(regs[1]), "=c"(regs[2]), "=d"(regs[3]) : "a"(i), "c"(0));
    // ECX is set to zero for CPUID function 4
#    endif
}
#endif