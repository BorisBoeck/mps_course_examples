/*
 * app.c
 *
 *  Created on: 24.10.2026
 *      Author: bboeck
 */


#include <msp430.h>

#include "app.h"


#define ADC_PIN     BIT4


/*
 * Global variable so that it can easily be observed
 * in the CCS debugger.
 */
unsigned int adc_value = 0;


void app_init(void)
{
    /*
     * Configure P1.4 / A4 as analog input.
     */
    ADC10AE0 |= ADC_PIN;

    /*
     * Select ADC input channel A4.
     */
    ADC10CTL1 = INCH_4;

    /*
     * ADC10:
     * - sample-and-hold time
     * - ADC switched on
     *
     * Reference voltage:
     * AVCC / AVSS
     */
    ADC10CTL0 = ADC10SHT_2 | ADC10ON;
}


void app_loop(void)
{
    /*
     * Start one ADC conversion.
     */
    ADC10CTL0 |= ENC | ADC10SC;

    /*
     * Wait until conversion is complete.
     *
     * This is deliberately implemented using polling.
     */
    while (ADC10CTL1 & ADC10BUSY)
    {
    }

    /*
     * Read 10-bit conversion result.
     */
    adc_value = ADC10MEM;
}
