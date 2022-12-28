/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : UART_PROG_C                                           */
/* Describtion   : UART communication protocol driver module.c file      */
/* Date          : Oct 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/

#define _XTAL_FREQ 16000000
#include <xc.h>

#include "Std_Types.h"
#include "MANIPULATOR.h"

#include "UART_cfg.h"
#include "UART_int.h"
#include "UART_prvt.h"



/***************************************************************************/
/*NOTE:communication type(Synchronous/Asynchronous) is definded in cfg file*/
/***************************************************************************/
/*
 * This function must be called before any usage for the module Tx/Rx.
 */
void UART_voidInit (void)
{
    float32 SprgCal = SPRGH_VAL(myBR);
    /*Round the value*/
    if (SprgCal-(uint32)SprgCal > 0.5) SprgCal +=1;
    #if     COMM_MODE == ASYNCHRONOUS
    /*High BRG or not*/
    MAN_BIT(mTXSTA,2,BRG_HIGH_SPEED);
    /*16 or 8 bit BRG*/
    MAN_BIT(mBAUDCON,3,BRG_WIDTH);
    /*Assign the register value to generate the needed baudrate*/
    mSPBRGH = (uint8)GET_BYTE((uint32)SprgCal,8);
    mSPBRG  = (uint8)GET_BYTE((uint32)SprgCal,0);
    
    mBaudRate = myBR;
    /*Clearing SYNC bit*/
    BIT_L(mTXSTA,4);
    /*Enabling the port*/
    BIT_H(mRCSTA,7);
    /*Choosing 9/8 bit with*/
    MAN_BIT(mTXSTA,6,DATA_WIDTH);
    MAN_BIT(mRCSTA,6,DATA_WIDTH);
    #if DATA_WIDTH == _9BIT
    /*Address or data bit*/
    MAN_BIT(mRCSTA,3,NINTH_BIT);
    #endif /*9th bit is add or data*/
    /*Idle state of Tx bin*/
    MAN_BIT(mBAUDCON,4,TX_PIN_IDLE);
    #if AUTO_BR_DETECT_FEATURE == 1
    /*tobe done..*/
    #endif /*AUTO_BR_DETECT_FEATURE*/
    #elif   COMM_MODE == SYNCHRONOUS
    /*tobe done..*/
    #endif
}

/**************************************************************************/
/***************************Simple communication***************************/
/**************************************************************************/
/*
 * Send a msg and stay there untill TX complete
 */
void UART_TxMsgSyn  (uint8 msg,uint16 TimeOutCount)
{
    uint16 i = TimeOutCount;
    /*Enable Tx module*/
    BIT_H(mTXSTA,5);
    /*Load and stard transmission*/
    mTXREG = msg;
    /*wait the tranmission to complete*/
    while (GET_BIT(mTXSTA,1) && i != 0) i--;
}

/*
 * Receive a msg. Wait until a time out counts is gone
 */
sint16 UART_RxMsgSyn  (uint16 TimeOutCount)
{
   
    /*Enable Rx module*/
    BIT_H(mRCSTA,4);
    while (!GET_BIT(mPIR1,5))
    { 
        TimeOutCount--;
        if (TimeOutCount == 0 ) return RX_TIME_OUT;
    }
    /*There is data received*/
    /*Check if data is OK*/
    if (GET_BIT(mRCSTA,2)) return FRAME_ERROR; 
    /*date is ok and ready to be read*/
    return mRCREG;
}

/*
 * Recive a msg but return and a call back fn wil handle the msg in ISR.
 * ISR must be enabbled and the call back must be called there  
 */
void UART_RxMsgAsyn (void)
{
    /*Enable Rx module*/
    BIT_H(mRCSTA,4);
}
/*If data is an msg only*/
sint16 Rx_ISR_msgHandler(void)
{
    /*Clear the flag*/
    BIT_L(mPIR1,5);
    /*There is data received, Disabele the module*/
    BIT_L(mRCSTA,4);
    /*Check if data is OK*/
    if (GET_BIT(mRCSTA,2)) return FRAME_ERROR; 
    /*date is ok and ready to be read*/
    return mRCREG;
}
/*if data is an array*/
void Rx_ISR_arrHandler(sint16 * msg, uint8 ArrSize,uint16 TimeOutCount)
{
    /*There is data received*/
    for (uint8 i =0;i<ArrSize;i++)
    {
        /*Clear the flag*/
        BIT_L(mPIR1,5);
        /*Check if data is OK*/
        if (GET_BIT(mRCSTA,2)) msg[i] = FRAME_ERROR; 
        /*date is ok and ready to be read*/
        else msg[i] = mRCREG;
        /*If no another data is here, wait some cycles before the next read*/
        while (!GET_BIT(mPIR1,5) && TimeOutCount != 0)
            TimeOutCount--;
    }
}
/**************************************************************************/
/************************Back to back communication************************/
/**************************************************************************/
/*
 * Send an array of msgs/chars and return.
 * TX completetion is handeled in ISR (if enabled)
 */
void UART_TxArrMsg (uint8 * msgArr, uint8 ArrSize)
{
    uint8 i = 0;
    /*Enable Tx module*/
    BIT_H(mTXSTA,5);
    while (i<ArrSize)
    {
        /*write the next word*/
        mTXREG = msgArr[i++];
        /*Wait untill TxReg is empty(TXIF)*/
        while (!GET_BIT(mPIR1,4));
    }
    /*Disable Tx module*/
    BIT_L(mTXSTA,5);
}

/*
 * Receive an array of msgs. 
 * Wait until a time out counts is gone with no data received
 */
void UART_RxArrMsg  (uint8* msg, uint8 ArrSize, uint16 TimeOutCount)
{
    uint8 i;
    /*Start the module to receive*/
    //UART_RxMsgAsyn();
   // Rx_ISR_arrHandler(msg,ArrSize,TimeOutCount);
    for (i=0;i<ArrSize;i++) msg[i] =(uint8) UART_RxMsgSyn  (TimeOutCount);
}
/**************************************************************************/

/*
* By default, baud rate is initialized by the configured value. If you need to change call this
*/
void UART_ReSetBaudRate (uint32 BR)
{
    SPRGH_VAL(BR);
    mBaudRate = BR;
}

/*Returns the actual baud rate*/
uint32 UART_getBaudRate(void)
{
    return mBaudRate;
}