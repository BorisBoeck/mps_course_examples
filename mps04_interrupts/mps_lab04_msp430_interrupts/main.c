/**********************************************************************************
*
*   MPS_Lab04:   msp430_interrupts
*   Interrupt mechanism and the event-driven software pattern
*   Uses a GPIO interrupt and a periodic Timer_A interrupt to generate software events.
*    The ISRs only report events; the application processes them.
*
*   P1.0 red LED: toggled every 500 ms based on the 10 ms system tick
*   P1.3 button: GPIO interrupt
*   P1.6 green LED: toggled once for each detected button event
*
*   Hardware / ISR              Application
*
*   button.c
*     │
*     └── button event ───────► app.c
*
*   systick.c
*     │
*     └── tick event ─────────► app.c
*                                 │
*                                 ▼
*                                led.c
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
