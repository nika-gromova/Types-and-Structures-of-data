#include "time.h"

unsigned long long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A"(d));
    return d;
}
