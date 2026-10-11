/**********************************************************************************
*
*   MPS_Lab02:   msp430_blinky
*   Let LED1 (P1.0) blink
*
*   Quartz: -
*
*   ACLK = n/a, MCLK = SMCLK = default DCO
*
*
***********************************************************************************/


#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= BIT0;

    while (1)
    {
        P1OUT |= BIT0;
        __delay_cycles(500000);

        P1OUT &= ~BIT0;
        __delay_cycles(500000);
    }
}
