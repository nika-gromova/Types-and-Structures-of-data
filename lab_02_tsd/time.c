#include "time.h"
/**
 * @brief tick Функция замера тактов.
 * @return d - количество тактов.
 */
unsigned long long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A"(d));
    return d;
}
