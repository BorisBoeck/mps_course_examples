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
    WDTCTL = WDTPW | WDTHOLD;

    app_init();

    while (1)
    {
        app_loop();
    }
}
