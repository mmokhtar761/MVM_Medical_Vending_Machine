/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : UART_CFG_H                                            */
/* Describtion   : UART communication protocol driver cinfig file        */
/* Date          : Nov 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef UART_CFG_H
#define UART_CFG_H

/*Options: */
#define ASYNCHRONOUS  1
#define SYNCHRONOUS   2
#define COMM_MODE       ASYNCHRONOUS

/**************************************************************************/
/*********************Synchronous mode Configurations**********************/
/**************************************************************************/
#if COMM_MODE == SYNCHRONOUS
    /*Options: */
    #define MASTER_NODE  1
    #define SLAVE_NODE   2
    #define MASTER_SLAVE_SEL MASTER_NODE SLAVE_NODE

    /*Options: */
    /*1 for enable 0 to disable*/
    #define CONTINUOUS_RX 1

    /*Options: */
    #define IDLE_LOW     0
    #define IDLE_HIGH    1
    #define CLK_IDLE  IDLE_LOW

    /*Options: */
    /*1 for enable 0 to disable*/
    #define CONTINUOUS_RX 1
#endif /*COMM_MODE SYNCH*/
/**************************************************************************/
/*********************Asynchronous mode Configurations*********************/
/**************************************************************************/
#if COMM_MODE == ASYNCHRONOUS
    /*Options: */
    /*1 for enable 0 to disable*/
    #define SEND_BREAK_CHAR 0

    /*Options: */
    #define IDLE_LOW     0
    #define IDLE_HIGH    1
    #define TX_PIN_IDLE  IDLE_LOW

    /*Options: */
    /*Parity
     *is not supported by the hardware but can be
     *implemented in software and stored as the 9th data bit.
     */
    #define DISABLE_P 0
    #define EVEN      1
    #define ODD       2
    #define POLARITY DISABLE

    /*Options: */
    /*1 for enable 0 to disable*/
    #define AUTO_BR_DETECT_FEATURE 0
#endif /*COMM_MODE ASYN*/
/**************************************************************************/
/**************************Generic Configurations**************************/
/**************************************************************************/
#define MY_Fosc ((uint32)16000000) /*Hz*/
/*Options: */
#define _8BIT 0
#define _9BIT 1
#define DATA_WIDTH _8BIT   


/**************************************************************************/
/*************************Baud Rate Configurations*************************/
/**************************************************************************/
/*Options: */
#define _8_BIT   0 /*Comapatible mode*/
#define _16_BIT  1
#define BRG_WIDTH _16_BIT

/*Options: */
/*1 for enable 0 to disable*/
#define BRG_HIGH_SPEED 1

/*Baud rate*/
#define myBR   (uint32)115200


/**************************************************************************/
/***************************Register definitions***************************/
/**************************************************************************/
/*Note: Iam using mblab, no need for actual addreses*/
#define mRCSTA   RCSTA
#define mTXREG   TXREG
#define mRCREG   RCREG
#define mTXSTA   TXSTA
#define mBAUDCON BAUDCON
#define mSPBRGH  SPBRGH
#define mSPBRG   SPBRG
#define mPIR1    PIR1

#endif  /*UART_CFG_H*/