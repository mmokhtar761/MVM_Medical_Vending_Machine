/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

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

#define INPUT 1
#define OUTPUT 0

#define ENABLE_FOR_CONFIG 1


#if ENABLE_FOR_CONFIG
/* Ports state */
uint8 PORT_A_DEF[8]= {OUTPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT,  /*PIN 2*/
                      OUTPUT,  /*PIN 3*/
                      OUTPUT,  /*PIN 4*/
                      OUTPUT,  /*PIN 5*/
                      OUTPUT,  /*PIN 6*/
                      OUTPUT}; /*PIN 7*/

uint8 PORT_B_DEF[8]= {OUTPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT,  /*PIN 2*/
                      OUTPUT,  /*PIN 3*/
                      OUTPUT,  /*PIN 4*/
                      OUTPUT,  /*PIN 5*/
                      OUTPUT,  /*PIN 6*/
                      OUTPUT}; /*PIN 7*/

uint8 PORT_C_DEF[8]= {OUTPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT,  /*PIN 2*/
                      OUTPUT,  /*PIN 3*/
                      OUTPUT,  /*PIN 4*/
                      OUTPUT,  /*PIN 5*/
                      OUTPUT,  /*PIN 6*/
                      OUTPUT}; /*PIN 7*/

uint8 PORT_D_DEF[8]= {OUTPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT,  /*PIN 2*/
                      OUTPUT,  /*PIN 3*/
                      OUTPUT,  /*PIN 4*/
                      OUTPUT,  /*PIN 5*/
                      OUTPUT,  /*PIN 6*/
                      OUTPUT}; /*PIN 7*/

uint8 PORT_E_DEF[8]= {OUTPUT,  /*PIN 0*/
                      OUTPUT,  /*PIN 1*/
                      OUTPUT}; /*PIN 2*/
                   



                          
#endif




#endif	/* DIO_CFG_H */

