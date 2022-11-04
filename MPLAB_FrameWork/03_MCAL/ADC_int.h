/*
 * ADC_int.h
 *
 *  Created on: Aug 23, 2021
 *      Author: Omar Nasr
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_



/*ADC initialization*/
void ADC_VoidInit(void);

/*Reading the value of the ADC*/
uint16 ADC_u16GetChannelReading(uint8 Channel);


#endif /* MCAL_ADC_ADC_INT_H_ */
