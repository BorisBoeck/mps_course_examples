/**********************************************************************************
*
*   MPS_Lab05:   msp430_adc
*   Read an analog voltage from a potentiometer and observe the 10-bit ADC result in the debugger.
*   Connect the potentiometer wiper to P1.4/A4.
*   Observe adc_value in the CCS debugger while turning the potentiometer.
*
*   P1.4  adc input (A4)
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
