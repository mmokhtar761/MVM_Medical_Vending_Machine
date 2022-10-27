/*
 * File:   newmain.c
 * Author: Mohamed Mokhtar
 *
 * Created on 23 October 2022, 20:56
 */

#define _XTAL_FREQ 16000000
#include "Std_Types.h"
#include "Config_uC.h"
#include "STPR_int.h"
void main(void) {
        while (1)
        {
         TRISC = 0x0;
         PORTC = 0xFF;
         __delay_ms(1000);
         PORTC = 0;
         __delay_ms(1000);
        }
    return;
}
