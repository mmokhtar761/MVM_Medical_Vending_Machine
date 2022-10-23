/*
 * File:   newmain.c
 * Author: Mohamed Mokhtar
 *
 * Created on 23 October 2022, 20:56
 */


#include <xc.h>
#include "Config_uC.h"
void main(void) {
    TRISB = 0x0;
    PORTB = 0xFF;
    while (1);
    return;
}
