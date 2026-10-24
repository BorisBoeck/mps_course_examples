/*
 * led.c
 *
 *  Created on: 24.10.2026
 *      Author: bboeck
 */


#include <msp430.h>

#include "led.h"


#define RED_LED_PIN      BIT0
#define GREEN_LED_PIN    BIT6


void led_init(void)
{
    /*
     * Configure LED pins as GPIO.
     */
    P1SEL  &= ~(RED_LED_PIN | GREEN_LED_PIN);
    P1SEL2 &= ~(RED_LED_PIN | GREEN_LED_PIN);

    /*
     * Configure LED pins as outputs.
     */
    P1DIR |= RED_LED_PIN | GREEN_LED_PIN;

    /*
     * Initial state: both LEDs off.
     */
    P1OUT &= ~(RED_LED_PIN | GREEN_LED_PIN);
}


void led_red_on(void)
{
    P1OUT |= RED_LED_PIN;
}


void led_red_off(void)
{
    P1OUT &= ~RED_LED_PIN;
}


void led_red_toggle(void)
{
    P1OUT ^= RED_LED_PIN;
}


void led_green_on(void)
{
    P1OUT |= GREEN_LED_PIN;
}


void led_green_off(void)
{
    P1OUT &= ~GREEN_LED_PIN;
}


void led_green_toggle(void)
{
    P1OUT ^= GREEN_LED_PIN;
}
