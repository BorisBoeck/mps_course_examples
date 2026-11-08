/*
 * itoa.h
 *
 *  Created on: 08.11.2026
 *      Author: bboeck
 */

#ifndef ITOA_H_
#define ITOA_H_



/**
 * @brief Converts an integer into a null-terminated string.
 *
 * @param value  Integer value to convert.
 * @param text   Destination character array.
 * @param base   Number base (2...16).
 *
 * @return Pointer to text.
 */
char *itoa(int value, char *text, int base);


#endif /* ITOA_H_ */


