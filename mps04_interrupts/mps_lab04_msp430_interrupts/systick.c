/*
 * systick.c
 *
 *  Created on: 24.10.2026
 *      Author: bboeck
 */


#include <msp430.h>
#include <stdbool.h>

#include "systick.h"


/*
 * One system tick every 10 ms.
 *
 * SMCLK = 1 MHz
 * Divider = 8
 *
 * Timer clock:
 *
 * 1 MHz / 8 = 125 kHz
 *
 * Required number of timer counts:
 *
 * 125000 Hz * 0.010 s = 1250
 *
 * Timer counts from 0 to CCR0:
 *
 * CCR0 = 1249
 */
#define SYSTICK_CCR0    1249


/*
 * Event flag shared with the Timer ISR.
 */
static volatile bool tick_event = false;


/*
 * Configure the MSP430 DCO for 1 MHz.
 *
 * For a larger project, clock configuration would usually
 * be placed in a separate system/clock module.
 */
static void clock_init_1mhz(void)
{
    /*
     * Check whether calibration constants are available.
     */
    if (CALBC1_1MHZ == 0xFF)
    {
        /*
         * Calibration data missing.
         */
        while (1)
        {
        }
    }

    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
}


/*
 * Initialize Timer_A0 as a 10 ms periodic system tick.
 */
void systick_init(void)
{
    clock_init_1mhz();

    tick_event = false;

    /*
     * Timer period.
     */
    TA0CCR0 = SYSTICK_CCR0;

    /*
     * Clear possible interrupt flag.
     */
    TA0CCTL0 &= ~CCIFG;

    /*
     * Enable CCR0 interrupt.
     */
    TA0CCTL0 |= CCIE;

    /*
     * Timer_A configuration:
     *
     * TASSEL_2 -> SMCLK
     * ID_3     -> divide by 8
     * MC_1     -> Up Mode
     * TACLR    -> clear timer
     */
    TA0CTL = TASSEL_2
           | ID_3
           | MC_1
           | TACLR;
}


/*
 * Return true if a system tick occurred.
 *
 * Reading the event clears it.
 */
bool systick_get_event(void)
{
    bool event;

    unsigned int gie_state = __get_SR_register() & GIE;

    __disable_interrupt();

    event = tick_event;
    tick_event = false;

    if (gie_state)
    {
        __enable_interrupt();
    }

    return event;
}


/*
 * Timer_A0 CCR0 Interrupt Service Routine
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer0_a0_isr(void)
{
    /*
     * CCR0 interrupt flag is automatically cleared
     * when the ISR is entered.
     */

    tick_event = true;
}
