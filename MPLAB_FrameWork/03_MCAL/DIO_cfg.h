/* 
 * File:   DIO_cfg.h
 * Author: Omar Nasr
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DIO_CFG_H
#define	DIO_CFG_H


#define ENABLE_FOR_CONFIG 1

#if ENABLE_FOR_CONFIG == 1
/* Ports state */
uint8 PORT_A_DEF[8]= {INPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT,  /*PIN 2*/
                      OUTPUT,  /*PIN 3*/
                      OUTPUT,  /*PIN 4*/
                      OUTPUT,  /*PIN 5*/
                      OUTPUT,  /*PIN 6*/
                      OUTPUT}; /*PIN 7*/

uint8 PORT_B_DEF[8]= {INPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT,  /*PIN 2*/
                      OUTPUT,  /*PIN 3*/
                      OUTPUT,  /*PIN 4*/
                      OUTPUT,  /*PIN 5*/
                      OUTPUT,  /*PIN 6*/
                      OUTPUT}; /*PIN 7*/

uint8 PORT_C_DEF[8]= {OUTPUT,  /*PIN 0*/
                      INPUT,  /*PIN 1*/
                      OUTPUT,  /*PIN 2*/
                      OUTPUT,  /*PIN 3*/
                      INPUT,  /*PIN 4*/
                      OUTPUT,  /*PIN 5*/
                      OUTPUT,  /*PIN 6*/
                      INPUT}; /*PIN 7*/

uint8 PORT_D_DEF[8]= {OUTPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT,  /*PIN 2*/
                      OUTPUT,  /*PIN 3*/
                      OUTPUT,  /*PIN 4*/
                      OUTPUT,  /*PIN 5*/
                      OUTPUT,  /*PIN 6*/
                      OUTPUT}; /*PIN 7*/

uint8 PORT_E_DEF[3]= {OUTPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT}; /*PIN 2*/                        
#endif


#define INIT_PORTA_VAL 0x0
#define INIT_PORTB_VAL 0x0
#define INIT_PORTC_VAL 0x0
#define INIT_PORTD_VAL 0x0
#define INIT_PORTE_VAL 0x0

#endif	/* DIO_CFG_H */

