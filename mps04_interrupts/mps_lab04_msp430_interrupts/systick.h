/*
 * systick.h
 *
 *  Created on: 24.10.2026
 *      Author: bboeck
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdbool.h>

void systick_init(void);
bool systick_get_event(void);

#endif /* SYSTICK_H_ */
