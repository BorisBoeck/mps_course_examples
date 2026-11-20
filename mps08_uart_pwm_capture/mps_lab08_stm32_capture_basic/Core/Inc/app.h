/*
 * app.h
 *
 *  Created on: 19.11.2026
 *      Author: bboeck
 */

#ifndef APP_H_
#define APP_H_

#include <stdint.h>


void app_init(void);
void app_loop(void);


/*
 * Variables for observation in the debugger.
 */
extern volatile uint16_t capture_delta;
extern volatile uint32_t measured_frequency_hz;


#endif /* APP_H_ */
