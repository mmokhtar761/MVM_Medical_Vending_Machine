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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _DIO_INT_H
#define _DIO_INT_H

/* Port Definition */
typedef enum  {
  PORT_A,
  PORT_B,
  PORT_C,
  PORT_D,
  PORT_E
}PORTS; 
/* PIN Definition */
typedef enum  {
  PIN0,
  PIN1,
  PIN2,
  PIN3,
  PIN4,
  PIN5,
  PIN6,
  PIN7
}PINS; 

/*Max number of pins for port E*/
#define PORT_E_LAST_PIN 2

/* PIN Directions */
#define INPUT            1
#define INPUT_PORT       255
#define OUTPUT           0
#define OUTPUT_PORT      0

/* PIN Value Options */
#define HIGH              1
#define HIGH_PORT         255
#define LOW               0
#define LOW_PORT          0

#define FIRST_HALF 1
#define SECOND_HALF 2

/*
 * Prototypes
 */
/* Pin Related Prototypes */
/* Set pin as Output or Input */
void DIO_VidSetPinDirection (uint8 u8PortIdCopy, uint8 u8PinIdCopy, uint8 u8PinDirCopy);

/* if pin is output - Set high or low voltage*/
void DIO_VidSetPinValue(uint8 u8PortIdCopy , uint8 u8PinIdCopy, uint8 u8PinValCopy);

/* if pin is input - get value */
uint8 DIO_u8GetPinValue(uint8 u8PortIdCopy, uint8 u8PinIdCopy);

/* Port Related Prototypes */
/* Set port direction */
void DIO_VidSetPortDirection (uint8 u8PortId, uint8 u8PortDir);

/* if port is output - Set high or low on all pins */
void DIO_VidSetPortValue    (uint8 u8PortId, uint8 u8PortVal);

/*initialize all pins direction*/
void DIO_Inti(void);

/*initialize the direction of Half a port (use FIRST_HALF or SECOND_HALF)*/ 
void DIO_VidSetHalfPortDirection(uint8 u8PortId, uint8 u8PortHalf ,uint8 u8PortDir);

/*initialize the value of Half a port (use FIRST_HALF or SECOND_HALF)*/ 
void DIO_VidSetHalfPortSet(uint8 u8PortId, uint8 u8PortHalf ,uint8 u8PortVal);

/*initialize the direction of Half a port (use start pin)*/
void DIO_VidDirPortNibble(uint8 u8PortId, uint8 u8StPin ,uint8 u8PortVal);

/*initialize the value of Half a port (use start pin)*/
void DIO_VidSetPortNibble(uint8 u8PortId, uint8 u8StPin ,uint8 u8PortVal);

/* if 4 pins are input - get value */
uint8 DIO_u8GetPortNibble(uint8 u8PortIdCopy , uint8 u8StPin );

/* if PORT is input - get value */
uint8 DIO_u8GetPortValue(uint8 u8PortIdCopy);

#endif