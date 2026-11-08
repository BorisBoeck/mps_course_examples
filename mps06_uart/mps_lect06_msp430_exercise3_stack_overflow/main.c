/**********************************************************************************
*
*   MPS_lect06:   msp430_exercise3_stack_overflow
*
*   Quartz: -
*
*   ACLK = n/a, MCLK = SMCLK = default DCO
*
*
***********************************************************************************/


#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


volatile char first_character;

/*
 * Guard values used to detect memory corruption.
 */
volatile uint16_t guard[8] =
{
    0xA000,
    0xA001,
    0xA002,
    0xA003,
    0xA004,
    0xA005,
    0xA006,
    0xA007
};


#define STACK_PADDING_SIZE    240


static void build_status_message(void)
{
    /*
     * Deliberately large local objects.
     *
     * Local automatic variables normally use the stack.
     */
    volatile uint8_t stack_padding[STACK_PADDING_SIZE];
    char    i;

    char message[48];


    /*
     * Make sure the array really exists and is accessed.
     */
    for(i=0; i<STACK_PADDING_SIZE; i++){
        stack_padding[i] = i;
    }


    /*
     * Convenient, but relatively expensive formatted output.
     */
    sprintf(message,
            "MODE=%u ADC=%u PWM=%u%%",
            2u,
            512u,
            50u);


    /*
     * BREAKPOINT AFTER SPRINTF
     */
    __no_operation();


    first_character = message[0];
}


static bool guard_is_valid(void)
{
    return
        (guard[0] == 0xA000) &&
        (guard[1] == 0xA001) &&
        (guard[2] == 0xA002) &&
        (guard[3] == 0xA003) &&
        (guard[4] == 0xA004) &&
        (guard[5] == 0xA005) &&
        (guard[6] == 0xA006) &&
        (guard[7] == 0xA007);
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;


    /*
     * BREAKPOINT BEFORE FUNCTION CALL
     *
     * At this point the guard values are still valid.
     *
     * Set a write watchpoint on guard[7] before continuing.
     */
    __no_operation();


    build_status_message();


    /*
     * Detect memory corruption.
     */
    if (!guard_is_valid())
    {
        P1OUT |= BIT0;
    }


    /*
     * BREAKPOINT AFTER FUNCTION CALL
     */
    __no_operation();


    while (1)
    {
    }
}
