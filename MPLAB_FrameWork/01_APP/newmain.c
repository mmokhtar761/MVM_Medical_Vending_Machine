/*
 * File:   newmain.c
 * Author: Mohamed Mokhtar
 *
 * Created on 23 October 2022, 20:56
 */


#include <xc.h>
#include "Config_uC.h"
#include "Platform_Types.h"
#include "MANIPULATOR.h"



#include "DIO_cfg.h"
#include "DIO_int.h"



void main(void) {
 DIO_VidSetHalfPortDirection(PORT_B, SECOND_HALF ,OUTPUT);
 DIO_VidSetHalfPortSet(PORT_B,SECOND_HALF,HIGH);
    while (1);
    return;
}
