/**********************************************************************************
*
*   MPS_lect06:   msp430_exercise1_follow_the_stack
*
*   Quartz: -
*
*   ACLK = n/a, MCLK = SMCLK = default DCO
*
*
***********************************************************************************/


#include <msp430.h>
#include <stdint.h>


volatile uint16_t result = 0;


static void level_3(uint16_t value)
{
    volatile uint16_t local_c = value + 3;
    volatile uint8_t frame_c[12];

    frame_c[0]  = 0xC0;
    frame_c[11] = 0xC1;

    /*
     * BREAKPOINT C
     *
     * Inspect:
     * - Call Stack
     * - SP (R1)
     * - local_c
     * - frame_c
     */
    __no_operation();

    result = local_c + frame_c[0] + frame_c[11];
}


static void level_2(uint16_t value)
{
    volatile uint16_t local_b = value + 2;
    volatile uint8_t frame_b[8];

    frame_b[0] = 0xB0;
    frame_b[7] = 0xB1;

    /*
     * BREAKPOINT B
     */
    __no_operation();

    level_3(local_b);

    /*
     * BREAKPOINT B RETURN
     */
    __no_operation();
}


static void level_1(uint16_t value)
{
    volatile uint16_t local_a = value + 1;
    volatile uint8_t frame_a[6];

    frame_a[0] = 0xA0;
    frame_a[5] = 0xA1;

    /*
     * BREAKPOINT A
     */
    __no_operation();

    level_2(local_a);

    /*
     * BREAKPOINT A RETURN
     */
    __no_operation();
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    level_1(10);

    while (1)
    {
        __no_operation();
    }
}

