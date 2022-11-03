/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : UART_PRVT_H                                           */
/* Describtion   : UART communication protocol driver private file       */
/* Date          : Nov 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef UART_PRVT_H
#define UART_PRVT_H

#define F_CYCLE (MY_Fosc/4)
/*SPRGH_VAL formula*/
#if    COMM_MODE == SYNCHRONOUS
    #define SPRGH_VAL(BR) (F_CYCLE/(BR*4) - 1.0)
#elif  COMM_MODE == ASYNCHRONOUS
    #if   (BRG_WIDTH == _8_BIT && BRG_HIGH_SPEED == 0)
    //uint8 myBaudRte = MY_Fosc/(64)
    #define SPRGH_VAL(BR) (F_CYCLE/(BR*16.0) - 1.0)

    #elif (BRG_WIDTH == _8_BIT && BRG_HIGH_SPEED == 1)
    #define SPRGH_VAL(BR) (F_CYCLE/(BR*4.0) - 1.0)

    #elif (BRG_WIDTH == _16_BIT && BRG_HIGH_SPEED == 0)
    #define SPRGH_VAL(BR) (F_CYCLE/(BR*4.0) - 1.0)

    #elif (BRG_WIDTH == _16_BIT && BRG_HIGH_SPEED == 1)
    #define SPRGH_VAL(BR) (F_CYCLE/(BR*1.0) - 1.0)
    #endif
#endif /*COMM_MODE ASYN*/


#define DATA_BIT 0
#define ADD_BIT  1
#if   DATA_WIDTH == 9 && AUTO_BR_DETECT_FEATURE == 1
#define NINTH_BIT ADD_BIT
#elif DATA_WIDTH == 9 && AUTO_BR_DETECT_FEATURE == 0
#define NINTH_BIT DATA_BIT
#endif /*DATA_WIDTH*/


#define FRAME_ERROR -1
#define RX_TIME_OUT -2
uint32 mBaudRate;

#endif /* UART_PRVT_H*/
