/* adapted from TI's msp430x21x2_ta0_01.c */
#include "msp430x21x2.h"
#include <signal.h>

extern void ta_intr();

#if defined(__clang__)
void Timer_A0 (void) __attribute__((interrupt(TIMER0_A0_VECTOR)));
void Timer_A0 (void)
#else
interrupt (TIMER0_A0_VECTOR) Timer_A0 (void)
#endif
{
    ta_intr();
}
