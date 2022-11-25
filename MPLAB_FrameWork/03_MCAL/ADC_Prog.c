/*
 * ADC_Prog.c
 *
 *  Created on: Aug 23, 2021
 *      Author: Omar Nasr
 */
#include <xc.h>

#include "Std_Types.h"
#include "MANIPULATOR.h"

#include "DIO_int.h"
#include "ADC_int.h"
#include "ADC_confg.h"

// frequancy definition
#define _XTAL_FREQ  4000000


void ADC_VoidInit(void){
    
    // set configuration pins 
    ADCON1 = (15- NUM_OF_AN_PINS) & 0x0f ;
    
    
	//voltage adjust V Ref.
    if(VREFP){BIT_H(ADCON1,4);}else{BIT_L(ADCON1,4);}
    if(VREFN){BIT_H(ADCON1,5);}else{BIT_L(ADCON1,5);}
    
	// ADC Prescaler (default 64)  (how to write: Prescaler_'number' )
    MAN_NIBBLE(ADCON2,0,Prescaler_64);
    
    //setting Acqusition time
    BIT_H(ADCON2,3);
    BIT_H(ADCON2,4);
	BIT_H(ADCON2,5);
    
    //setting justification type 
    MAN_BIT(ADCON2,7,JUST);

	// ADC Enable
	BIT_H(ADCON0,0);
}

uint16 ADC_u16GetChannelReading(uint8 Channel){
    uint16 u16ReadingReturn;
	//clear first 2-5 bits
	ADCON0 &= 0b11000011;
    
	//set the channel
	ADCON0 &= (Channel*4)+3 ;
    
    // wait for the capacitor to charge
     __delay_us(50);
	//start Conversion
	BIT_H(ADCON0,1);

    //wait until the flag is low
	while(GET_BIT(ADCON0,1)==1)
        ;
    

	//make sure it is low (optional)
	//BIT_L(ADCON0,1);
  
	//return the value in the registers
	if  (JUST){ u16ReadingReturn= ((uint16)ADRESH<<8) +(uint16)ADRESL   ;} /* return right justified 10-bit result */
    else      { u16ReadingReturn= (((uint16)ADRESH<< 8)|(uint16)ADRESL)>>6  ;} /* return left justified 10-bit result */
    
    return u16ReadingReturn;
}
