/*
 * ADC_priv.h
 *
 *  Created on: Aug 23, 2021
 *      Author: Omar Nasr
 */

#ifndef MCAL_ADC_ADC_PRIV_H_
#define MCAL_ADC_ADC_PRIV_H_

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
