/*
 * button.c
 *
 *  Created on: 24.10.2026
 *      Author: bboeck
 */


#include <msp430.h>
#include <stdbool.h>

#include "button.h"


#define BUTTON_PIN  BIT3


/*
 * Event flag shared between ISR and application.
 *
 * volatile is required because the variable can be modified
 * asynchronously by the interrupt service routine.
 */
static volatile bool button_event = false;


/*
 * Initialize pushbutton P1.3.
 *
 * The button is connected active LOW:
 *
 * released -> HIGH
 * pressed  -> LOW
 *
 * Therefore, we generate an interrupt on a
 * HIGH-to-LOW transition.
 */
void button_init(void)
{
    /* Configure P1.3 as GPIO */
    P1SEL  &= ~BUTTON_PIN;
    P1SEL2 &= ~BUTTON_PIN;

    /* Configure as input */
    P1DIR &= ~BUTTON_PIN;

    /* Enable internal pull resistor */
    P1REN |= BUTTON_PIN;

    /* Select pull-up resistor */
    P1OUT |= BUTTON_PIN;

    /*
     * Interrupt edge:
     *
     * P1IES = 1 -> HIGH-to-LOW
     */
    P1IES |= BUTTON_PIN;

    /*
     * Clear possible pending interrupt flag
     * before enabling the interrupt.
     */
    P1IFG &= ~BUTTON_PIN;

    /* Enable interrupt for P1.3 */
    P1IE |= BUTTON_PIN;

    button_event = false;
}


/*
 * Return true if a button event has occurred.
 *
 * Reading the event also clears it.
 */
bool button_get_event(void)
{
    bool event;

    /*
     * Prevent the ISR from modifying button_event
     * while it is being read and cleared.
     */
    unsigned int gie_state = __get_SR_register() & GIE;

    __disable_interrupt();

    event = button_event;
    button_event = false;

    if (gie_state)
    {
        __enable_interrupt();
    }

    return event;
}


/*
 * Port 1 Interrupt Service Routine
 */
#pragma vector=PORT1_VECTOR
__interrupt void port1_isr(void)
{
    if (P1IFG & BUTTON_PIN)
    {
        /*
         * Clear interrupt flag.
         */
        P1IFG &= ~BUTTON_PIN;

        /*
         * Report event to the application.
         *
         * Do not execute application logic here.
         */
        button_event = true;
    }
}
