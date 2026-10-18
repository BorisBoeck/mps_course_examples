/**********************************************************************************
*
*   MPS_Lab03:   msp430_timer
*   Timer with polling
*
*   Quartz: -
*
*   ACLK = n/a, MCLK = SMCLK = default DCO
*
*
***********************************************************************************/


#include <msp430.h>

#define LED_PIN         BIT0
#define TICKS_500_MS    50

int main(void)
{
    unsigned int tick_counter = 0;

    /* Stop watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;


    /* ------------------------------------------------------
     * Configure DCO for 1 MHz
     * ------------------------------------------------------ */

    if (CALBC1_1MHZ == 0xFF)
    {
        while (1)
        {
            /* Calibration data missing */
        }
    }

    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;


    /* ------------------------------------------------------
     * Configure status LED: P1.0
     * ------------------------------------------------------ */

    P1SEL  &= ~LED_PIN;
    P1SEL2 &= ~LED_PIN;

    P1DIR |= LED_PIN;
    P1OUT &= ~LED_PIN;


    /* ------------------------------------------------------
     * Configure Timer_A0
     *
     * SMCLK = 1 MHz
     * Divider = 8
     *
     * Timer clock:
     *
     * 1 MHz / 8 = 125 kHz
     *
     * Required timer period:
     *
     * 10 ms
     *
     * Number of timer counts:
     *
     * 125000 Hz * 0.010 s = 1250
     *
     * Timer counts from 0 ... CCR0,
     * therefore:
     *
     * CCR0 = 1249
     * ------------------------------------------------------ */

    TA0CCR0 = 1249;

    /* Clear possible pending compare flag */
    TA0CCTL0 &= ~CCIFG;

    /*
     * TASSEL_2 : SMCLK
     * ID_3     : divide clock by 8
     * MC_1     : Up mode
     * TACLR    : clear timer
     */
    TA0CTL = TASSEL_2
           | ID_3
           | MC_1
           | TACLR;


    /* ------------------------------------------------------
     * Main loop
     * ------------------------------------------------------ */

    while (1)
    {
        /*
         * Poll Timer_A compare flag.
         *
         * CCIFG becomes set whenever the timer reaches CCR0.
         */
        if (TA0CCTL0 & CCIFG)
        {
            /* Clear flag manually */
            TA0CCTL0 &= ~CCIFG;

            /*
             * One timer event = 10 ms
             */
            tick_counter++;

            /*
             * 50 * 10 ms = 500 ms
             */
            if (tick_counter >= TICKS_500_MS)
            {
                tick_counter = 0;

                /* Toggle LED */
                P1OUT ^= LED_PIN;
            }
        }
    }
}
