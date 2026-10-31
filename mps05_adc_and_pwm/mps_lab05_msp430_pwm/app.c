/*
 * app.c
 *
 *  Created on: 24.10.2026
 *      Author: bboeck
 */


#include <msp430.h>

#include "app.h"


#define PWM_PIN     BIT1


static void clock_init_1mhz(void)
{
    /*
     * Check whether factory calibration data exists.
     */
    if (CALBC1_1MHZ == 0xFF)
    {
        while (1)
        {
        }
    }

    /*
     * Configure DCO for 1 MHz.
     */
    DCOCTL = 0;

    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}


void app_init(void)
{
    clock_init_1mhz();


    /*
     * Configure P2.1 as Timer1_A output TA1.1.
     */
    P2DIR |= PWM_PIN;

    P2SEL  |= PWM_PIN;
    P2SEL2 &= ~PWM_PIN;


    /*
     * PWM period:
     *
     * SMCLK = 1 MHz
     *
     * 1000 counts -> 1 ms
     *
     * fPWM = 1 kHz
     */
    TA1CCR0 = 999;


    /*
     * Reset/set output mode for PWM.
     */
    TA1CCTL1 = OUTMOD_7;


    /*
     * 50 % duty cycle.
     *
     * HIGH time = 500 us
     */
    TA1CCR1 = 500;


    /*
     * Timer1_A:
     *
     * SMCLK
     * Up Mode
     * Clear timer
     */
    TA1CTL = TASSEL_2
           | MC_1
           | TACLR;
}


void app_loop(void)
{
    /*
     * Nothing required here.
     *
     * PWM is generated completely by the timer hardware.
     */
}
