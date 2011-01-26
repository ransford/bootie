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
    P3DIR |= 0x08;                            // P3.3 output
#else
    P1DIR |= 0x08;                            // P1.3 output
#endif

    for (i = 0; i < 20; ++i) {
        for (j = 0; j < 10000; ++j);

#ifdef __MSP430_2132__
        P3OUT ^= 0x08;                        // toggle P3.3
#else
        P1OUT ^= 0x08;                        // toggle P1.3
#endif

    }
}
