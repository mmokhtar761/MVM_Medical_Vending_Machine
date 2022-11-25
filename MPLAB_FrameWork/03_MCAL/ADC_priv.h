/*
 * ADC_priv.h
 *
 *  Created on: Aug 23, 2021
 *      Author: Omar Nasr
 */

#ifndef MCAL_ADC_ADC_PRIV_H_
#define MCAL_ADC_ADC_PRIV_H_



/* prescalur definition*/
typedef enum {
    Prescaler_2  =0,
    Prescaler_4  =4,
    Prescaler_8  =1,
    Prescaler_16 =5,
    Prescaler_32 =2,
    Prescaler_64 =6,
    Prescaler_FRC=7,
       
}PRESCALUR;

/* prescalur calculation*/
#define ADC_PRESCALUR(var)    (0b11111000+var)

/* number of analog pins */
#define  NUM_OF_AN_PINS  1


 

#endif /* MCAL_ADC_ADC_PRIV_H_ */
