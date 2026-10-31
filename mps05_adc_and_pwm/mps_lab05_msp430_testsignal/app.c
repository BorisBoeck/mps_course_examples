/*
 * app.c
 *
 *  Created on: 24.10.2026
 *      Author: bboeck
 */


#include <msp430.h>

#include "app.h"
#include "testpin.h"




static void clock_init_1mhz(void)
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


void app_init(void)
{
    clock_init_1mhz();

    TESTPIN1_INIT();        // Configure DEBUG pin
}


void app_loop(void)
{

    TESTPIN1_HIGH();        // Set DEBUG pin HIGH.


    /*
     * Known test interval:
     *
     * approximately 1000 CPU cycles
     * at 1 MHz -> approximately 1 ms
     */
    __delay_cycles(1000);



    TESTPIN1_LOW();        // Set DEBUG pin LOW.


    /*
     * Wait approximately 4 ms before
     * generating the next pulse.
     */
    __delay_cycles(4000);
}
