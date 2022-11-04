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
#include "ADC_confg.h"
#include "ADC_int.h"

#define _XTAL_FREQ  4000000



void main(void) {
 DIO_VidSetHalfPortDirection(PORT_A, FIRST_HALF ,INPUT);
 DIO_VidSetHalfPortDirection(PORT_C, FIRST_HALF ,OUTPUT);
unsigned int adc_value,temp ;
 ADC_VoidInit();
    while (1){
        
        adc_value= ADC_u16GetChannelReading(CHANNEL0);
        temp=((adc_value*5)/1023.0)*100;
        DIO_VidSetPinValue(PORT_C,PIN1,HIGH);
        DIO_VidSetPinValue(PORT_C,PIN2,HIGH);
        DIO_VidSetPinValue(PORT_C,PIN3,HIGH);
        if(temp>29){DIO_VidSetPinValue(PORT_C,PIN0,HIGH);}else{DIO_VidSetPinValue(PORT_C,PIN0,LOW);}
    }
    return;
}
