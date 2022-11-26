/*
 * EXTI_int.h
 *
 *  Created on: Aug 17, 2021
 *      Author: Omar Nasr
 */

#ifndef MCAL_EXTI_DIO_INT_H_
#define MCAL_EXTI_DIO_INT_H_


//prototypes
void GIE_Enable(void);
void GIE_Disable(void);

void EXIT_Int(void);

void EXIT0_Enable(void);
void EXIT0_Disable(void);

void EXIT1_Enable(void);
void EXIT1_Disable(void);

void EXIT2_Enable(void);
void EXIT2_Disable(void);

#endif /* MCAL_EXTI_DIO_INT_H_ */
