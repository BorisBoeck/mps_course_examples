/**********************************************************************************
*
*   Smart Fan Controller - MSP430
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
    /* Stop watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;

    /* Initialize application and hardware */
    app_init();

    /* Main application loop */
    while (1)
    {
        app_loop();
    }
}
