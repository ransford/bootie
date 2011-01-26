/* adapted from TI's msp430x21x2_ta0_01.c */
#ifdef __MSP430_2132__
#include <msp430x21x2.h>
#else
#include <msp430x21x1.h>
#endif

int main(void)
{
    unsigned int i, j;
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
#ifdef __MSP430_2132__
    P3DIR |= 0x02;                            // P3.1 output
#else
    P1DIR |= 0x02;                            // P1.1 output
#endif

    for (i = 0; i < 20; ++i) {
        for (j = 0; j < 10000; ++j);

#ifdef __MSP430_2132__
        P3OUT ^= 0x02;                        // toggle P3.1
#else
        P1OUT ^= 0x02;                        // toggle P1.1
#endif

    }
}
