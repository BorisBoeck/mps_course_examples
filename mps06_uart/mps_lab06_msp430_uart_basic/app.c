/*
 * app.c
 *
 *  Created on: 24.10.2026
 *      Author: bboeck
 */


#include <msp430.h>
#include <stdbool.h>

#include "app.h"
#include "itoa.h"


/*
 * UART receive event.
 *
 * These variables are shared between the ISR
 * and the main program.
 */
static volatile char rx_character = 0;
static volatile bool rx_event = false;


/*
 * Counts processed received characters.
 *
 * Kept below 10000 so that it always fits comfortably
 * into a signed int on the MSP430.
 */
static int rx_counter = 0;


/*
 * Configure system clock for 1 MHz.
 */
static void clock_init(void)
{
    if (CALBC1_1MHZ == 0xFF)
    {
        while (1)
        {
        }
    }

    DCOCTL = 0;

    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}


/*
 * Configure UART:
 *
 * 9600 baud
 * 8 data bits
 * no parity
 * 1 stop bit
 *
 * SMCLK = 1 MHz
 */
static void uart_init(void)
{
    /*
     * P1.1 = UCA0RXD
     * P1.2 = UCA0TXD
     */
    P1SEL  |= BIT1 | BIT2;
    P1SEL2 |= BIT1 | BIT2;


    /*
     * Hold USCI_A0 in reset while configuring.
     */
    UCA0CTL1 = UCSWRST;


    /*
     * SMCLK as UART clock source.
     */
    UCA0CTL1 |= UCSSEL_2;


    /*
     * 1 MHz / 9600 baud.
     */
    UCA0BR0 = 104;
    UCA0BR1 = 0;

    UCA0MCTL = UCBRS0;


    /*
     * Release UART from reset.
     */
    UCA0CTL1 &= ~UCSWRST;


    /*
     * Enable receive interrupt.
     */
    IE2 |= UCA0RXIE;
}


/*
 * Blocking transmission of one character.
 */
static void uart_send_char(char character)
{
    while (!(IFG2 & UCA0TXIFG))
    {
    }

    UCA0TXBUF = character;
}


/*
 * Blocking transmission of a null-terminated string.
 */
static void uart_send_string(const char *text)
{
    while (*text != '\0')
    {
        uart_send_char(*text);

        text++;
    }
}


void app_init(void)
{
    clock_init();

    uart_init();

    rx_counter = 0;

    uart_send_string("\r\nUART example ready\r\n");
    uart_send_string("Type a character...\r\n\r\n");
}


void app_loop(void)
{
    char character;
    char number_string[6];


    /*
     * Check whether the UART ISR reported
     * a received character.
     */
    if (rx_event)
    {
        /*
         * Copy shared information first.
         */
        character = rx_character;

        /*
         * Consume event.
         */
        rx_event = false;


        /*
         * Count processed input characters.
         */
        rx_counter++;

        if (rx_counter > 9999)
        {
            rx_counter = 1;
        }


        /*
         * Convert number into a decimal string.
         */
        itoa(rx_counter, number_string, 10);


        /*
         * Send response.
         */
        uart_send_string("Received #");
        uart_send_string(number_string);

        uart_send_string(": ");
        uart_send_char(character);

        uart_send_string("\r\n");
    }
}


/*
 * UART receive interrupt.
 */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void usci_rx_isr(void)
{
    if (IFG2 & UCA0RXIFG)
    {
        /*
         * Read received byte.
         */
        rx_character = UCA0RXBUF;

        /*
         * Report a new character to the application.
         */
        rx_event = true;
    }
}
