/**********************************************************************************
*
*   MPS_Lab06:   msp430_uart_basic
*   - configure the MSP430G2553 UART for 9600 8N1
*   - send a short startup message using blocking TX
*   - receive characters using the RX interrupt
*   - store one received character as an event
*   - echo the character back in app_loop()
*
*   Quartz: -
*
*   ACLK = n/a, MCLK = SMCLK = default DCO
*
*
***********************************************************************************/


#include <msp430.h>

#include "app.h"


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    app_init();

    __enable_interrupt();

    while (1)
    {
        app_loop();
    }
}
