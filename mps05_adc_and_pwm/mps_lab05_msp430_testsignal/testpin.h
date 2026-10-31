/*
 * testpin.h
 *
 *  Created on: 31.10.2026
 *      Author: bboeck
 */

#ifndef TESTPIN_H_
#define TESTPIN_H_


#include <msp430.h>


/* ----------------------------------------------------------
 * Test Pin 1
 *
 * Example: P2.0
 * ---------------------------------------------------------- */

#define TESTPIN1_PIN      BIT0

#define TESTPIN1_INIT()   do {          \
    P2SEL  &= ~TESTPIN1_PIN;            \
    P2SEL2 &= ~TESTPIN1_PIN;            \
    P2DIR  |=  TESTPIN1_PIN;            \
    P2OUT  &= ~TESTPIN1_PIN;            \
} while (0)

#define TESTPIN1_HIGH()   (P2OUT |=  TESTPIN1_PIN)
#define TESTPIN1_LOW()    (P2OUT &= ~TESTPIN1_PIN)
#define TESTPIN1_TOGGLE() (P2OUT ^=  TESTPIN1_PIN)


#endif /* TESTPIN_H_ */


