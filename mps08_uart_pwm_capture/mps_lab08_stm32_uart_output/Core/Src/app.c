/*
 * app.c
 *
 *  Created on: 19.11.2026
 *      Author: bboeck
 *      Show how a numerical value can be sent periodically to the PC terminal.
 *
 *      CubeMX configuration:
 *      USART2
 *		Mode:       Asynchronous
 *
 *		TX:         PA2
 *		RX:         PA15
 *
 *		Baud rate:  115200
 *		Data:       8 bit
 *		Parity:     none
 *		Stop:       1
 *
 *
 *
 */

#include "app.h"

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "usart.h"


#define OUTPUT_PERIOD_MS    500U


static uint32_t last_output_time = 0;
static unsigned int counter = 0;


static void send_counter(void)
{
    char text[32];

    int length = snprintf(text, sizeof(text), "Counter=%u\r\n", counter);

    if (length > 0)
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)text, (uint16_t)length, HAL_MAX_DELAY);
    }
}


void app_init(void)
{
    last_output_time = HAL_GetTick();
    counter = 0;

    HAL_UART_Transmit(&huart2, (uint8_t *)"UART output example\r\n", sizeof("UART output example\r\n") - 1U, HAL_MAX_DELAY);
}


void app_loop(void)
{
    uint32_t current_time = HAL_GetTick();

    if ((current_time - last_output_time) >= OUTPUT_PERIOD_MS)
    {
        last_output_time = current_time;

        counter++;

        send_counter();
    }
}
