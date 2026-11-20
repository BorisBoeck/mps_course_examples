/*
 * app.c
 *
 *  Created on: 19.11.2026
 *
 *      Author: bboeck
 *      Generate a known PWM signal and inspect frequency and duty cycle with the oscilloscope.
 *      Uses Pin D6/PB1, TIM3_CH4
 *
 *      CubeMX configuration:
 *      SYSCLK
 *      HSI => PLL => 64MHz
 *
 *      TIM3
 *      Clock Source:       Internal Clock
 *      Channel 4:          PWM Generation CH4
 *
 *      Prescaler:          63
 *      Counter Period:     999
 *      PWM Pulse:          initially 0
 *
 *	    => PWM frequency = 1kHz
 *
 */

#include "app.h"

#include "main.h"
#include "tim.h"


#define PWM_PERIOD_COUNTS    1000U


static void set_duty(unsigned int duty_percent)
{
    uint32_t compare;

    if (duty_percent > 100U)
    {
        duty_percent = 100U;
    }

    compare = (PWM_PERIOD_COUNTS * duty_percent) / 100U;

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, compare);
}


void app_init(void)
{
    /*
     * Start TIM3 Channel 4 PWM output.
     */
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

    set_duty(0);
}


void app_loop(void)
{
    set_duty(25);
    HAL_Delay(2000);

    set_duty(50);
    HAL_Delay(2000);

    set_duty(75);
    HAL_Delay(2000);
}
