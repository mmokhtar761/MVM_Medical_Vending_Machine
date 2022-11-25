/*
 * ADC_int.h
 *
 *  Created on: Aug 23, 2021
 *      Author: Omar Nasr
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

/*channel definition*/
typedef enum {
    CHANNEL0 ,
    CHANNEL1 ,
    CHANNEL2 ,
    CHANNEL3 ,
    CHANNEL4 ,
    CHANNEL5 ,
    CHANNEL6 ,
    CHANNEL7 ,
    CHANNEL8 ,
    CHANNEL9 ,
    CHANNEL10,
    CHANNEL11,
    CHANNEL12,            
}CHANNELS;

/*ADC initialization*/
void ADC_VoidInit(void);

/*Reading the value of the ADC*/
uint16 ADC_u16GetChannelReading(uint8 Channel);


#endif /* MCAL_ADC_ADC_INT_H_ */
