/**********************************************************************************
*
*   MPS_lect06:   msp430_exercise2_interrupt_stack
*
*   Quartz: -
*
*   ACLK = n/a, MCLK = SMCLK = default DCO
*
*
***********************************************************************************/


#include <msp430.h>
#include <stdint.h>


volatile uint16_t timer_interrupt_count = 0;


static void clock_init(void)
{
    if (CALBC1_1MHZ == 0xFF)
    {
        while (1)
        {
        }
    }

    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}


static void timer_init(void)
{
    /*
     * SMCLK = 1 MHz
     *
     * 50,000 timer counts = 50 ms
     */
    TA0CCR0 = 49999;

    TA0CCTL0 = CCIE;

    TA0CTL = TASSEL_2
           | MC_1
           | TACLR;
}


static void worker(void)
{
    volatile uint16_t value = 0;
    volatile uint16_t marker = 0x1234;

    while (1)
    {
        value++;

        marker ^= value;

        /*
         * The timer interrupt may occur
         * anywhere inside this loop.
         */
        __no_operation();
    }
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    clock_init();
    timer_init();

    __enable_interrupt();

    worker();

    while (1)
    {
    }
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer0_a0_isr(void)
{
    timer_interrupt_count++;

    __no_operation();
}
