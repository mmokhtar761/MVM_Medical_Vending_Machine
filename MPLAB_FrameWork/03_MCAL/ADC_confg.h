/*
 * ADC_confg.h
 *
 *  Created on: Aug 23, 2021
 *      Author: Omar Nasr
 */

#ifndef MCAL_ADC_ADC_CONFG_H_
#define MCAL_ADC_ADC_CONFG_H_

#include "ADC_priv.h"

/*ADC Read mode*/
#define JUST 1     // default 1 (1 ==> Right justified , 0 ==> left justified) 

/*Voltage source*/
#define VREFP  0  /* '0' default , 0 for VSS | 1 for AN2 */
#define VREFN  0  /* '0' default , 0 for VSS | 1 for AN2 */

#endif /* MCAL_ADC_ADC_CONFG_H_ */
