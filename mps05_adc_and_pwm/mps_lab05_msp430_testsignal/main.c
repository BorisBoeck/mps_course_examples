/**********************************************************************************
*
*   MPS_Lab05:   msp430_testsignal
*   Often we are interested in detailed information concerning timing in our applicatiuon
*   Idea:
*    - Create a test signal on a GPIO pin (switch high, switch low, toggle at points
*       of interest in the code)
*    - Observe the test signal with an oscilloscope
*
*   Example: Create here signal around a delay
*              (idea is to measure the run tiem of a certain function)
*
*            p2.0 ist used as test pin (see testpin.h)
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
