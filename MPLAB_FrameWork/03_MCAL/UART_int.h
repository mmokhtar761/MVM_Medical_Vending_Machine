/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : UART_INT_H                                            */
/* Describtion   : UART communication protocol driver interface file     */
/* Date          : Nov 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef UART_INT_H
#define UART_INT_H


#define FRAME_ERROR -1
#define RX_TIME_OUT -2
/***************************************************************************/
/*NOTE:communication type(Synchronous/Asynchronous) is definded in cfg file*/
/***************************************************************************/
/*
 * This function must be called before any usage for the module Tx/Rx.
 */
void UART_voidInit (void);
/**************************************************************************/
/***************************Simple communication***************************/
/**************************************************************************/
/*
 * Send a msg and stay there untill TX complete, or time out is gone
 * Once a interrupt is enabled for the module and a msg is written, an ISR is triggered 
 */
void UART_TxMsgSyn  (uint8 msg,uint16 TimeOutCount);

/*
 * Receive a msg. Wait until a time out counts is gone
 */
sint16 UART_RxMsgSyn  (uint16 TimeOutCount);

/*
 * Recive a msg but return and a call back fn wil handle the msg in ISR.
 * ISR must be enabbled and the call back(Rx_ISR_Handler) must be called there  
 */
void UART_RxMsgAsyn (void);
/*If data is an msg only*/
sint16 Rx_ISR_Handler(void);
/*if data is an array*/
void Rx_ISR_arrHandler(sint16* msg, uint8 ArrSize,uint16 TimeOutCount);


/**************************************************************************/
/************************Back to back communication************************/
/**************************************************************************/
/*
 * Send an array of msgs/chars and return.
 * TX completetion is handeled in ISR (if enabled)
 */
void UART_TxArrMsg (uint8 * msgArr, uint8 ArrSize);

/*
 * Receive an array of msgs. 
 * Wait until a time out counts is gone with no data received
 */
void UART_RxArrMsg  (sint16* msg, uint8 ArrSize, uint16 TimeOutCount);
/**************************************************************************/

/*
* By default, baud rate is initialized by the configured value. If you need to change call this
*/
void UART_ReSetBaudRate (uint32 BR);

/*Returns the actual baud rate*/
uint32 UART_getBaudRate(void);


#endif  /*UART_INT_H*/