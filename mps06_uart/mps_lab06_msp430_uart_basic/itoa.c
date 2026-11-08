/*
 * itoa.c
 *
 *  Created on: 08.11.2026
 *      Author: bboeck
 */
#include <stdbool.h>
#include "itoa.h"


static void reverse_string(char *text, unsigned int length)
{
    unsigned int i;
    char temp;

    for (i = 0; i < length / 2; i++)
    {
        temp = text[i];
        text[i] = text[length - 1 - i];
        text[length - 1 - i] = temp;
    }
}


char *itoa(int value, char *text, int base)
{
    unsigned int i = 0;
    unsigned int number;
    bool negative = false;

    if ((base < 2) || (base > 16))
    {
        text[0] = '\0';
        return text;
    }

    if (value < 0)
    {
        negative = true;
        number = (unsigned int)(-value);
    }
    else
    {
        number = (unsigned int)value;
    }

    do
    {
        unsigned int digit = number % base;

        if (digit < 10)
        {
            text[i++] = '0' + digit;
        }
        else
        {
            text[i++] = 'A' + (digit - 10);
        }

        number /= base;

    } while (number > 0);

    if (negative)
    {
        text[i++] = '-';
    }

    text[i] = '\0';

    reverse_string(text, i);

    return text;
}
