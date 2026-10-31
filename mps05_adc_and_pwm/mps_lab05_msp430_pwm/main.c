/**********************************************************************************
*
*   MPS_Lab05:   msp430_pwm
*   Generate a hardware PWM signal and inspect frequency and duty cycle with the oscilloscope.
*   Use Timer1_A, so Timer0_A can later remain available for the system tick.
*   T = 1ms, Duty cycle = 50%
*   Measure PWM signal with oscilloscope
*
*   P2.1  pwm output TA1.1  (CCR1 of TimerA1)
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
