/*
 * File:   newmain.c
 * Author: Mohamed Mokhtar
 *
 * Created on 23 October 2022, 20:56
 */

#define _XTAL_FREQ 16000000
/*Lib modules inc*/
#include "Config_uC.h"
#include "Std_Types.h"
#include "MANIPULATOR.h"

#include <stdio.h>
#include <string.h>
#include <math.h>


/*MCAL modules inc*/
#include "DIO_int.h"
#include "ADC_int.h"
#include "UART_int.h"


/*HAL modules inc*/
#include "STPR_int.h"
#include "LCD_int.h"

/*APP modules*/
#include "mainH.h"

                 sint16 mymsg;
                          uint16 val;


uint8 buffer[10];

/*first element represents the number of needed orders*/
/*the next 16 one are the max possiple actual orders*/
uint8 myOrders [MAX_ORDER_COUNT+1];

void main(void) {
    /*main counter*/
    uint8 i,item_index,count;
    /*Init the system HW modules*/
    INIT_SYS ();

    while (1)
    {
        LCD_SetCursor (1);
        LCD_wStr   ("    WELCOME    ");
        LCD_wStr   ("      MVM      ");
        
        do
        {
            //Update temp on LCD
            /*Check if any data received*/
            myOrders[OrderSizeIndex] = UART_RxMsgSyn  (myTimeOutCount);
        }while (myOrders[OrderSizeIndex] == FRAME_ERROR || myOrders[OrderSizeIndex] == RX_TIME_OUT);
        
        /*An order is required.....*/
        LCD_SetCursor (1);
        LCD_wCmd   ("  PLEASE  WAIT     LOADING...   ");
        if ( myOrders[OrderSizeIndex] > MAX_ORDER_COUNT) myOrders[OrderSizeIndex] =MAX_ORDER_COUNT;
        
        /*please receive an array of size myOrders[OrderSizeIndex] and put them in the array starting from FrstOrderIndex */
        UART_RxArrMsg  (myOrders+FrstOrderIndex, myOrders[OrderSizeIndex], myTimeOutCount);
        
        /*
         
         * confirm here that there is a person on the machine
         
         */
        
        /* A customer is waiting. Start serving orders */
        for (i=0;i<myOrders[OrderSizeIndex];i++)
        {
            /*
             * item_index 
             * count
             */
            /*Move lever to the required item row*/
            moveLvr2Row(GET_ROW(item_index));
            /*Start feeding the item...*/
            STPR_voidMoveStprStps (&MyStprs[FrstStepperUniqueID+item_index], count*200 , DIR_Low);
        }
        /*Move lever to the gate*/
        moveLvr2Row(0);
        
        /*Order is ready please take it*/
        LCD_SetCursor (1);
        LCD_wCmd   ("  PLEASE  TAKE     YOUR ORDER   ");
        __delay_ms(2000);
         
         //val = ADC_u16GetChannelReading(CHANNEL0);
         //mymsg = GetNTC_temp(val);
         //sprintf (buffer,mymsg );

        //UART_TxMsgSyn  ('x',100);
        //mymsg = UART_RxMsgSyn  (10000);
        //while(1);
        //__delay_ms(20);

        //STPR_voidMoveStprStps (MyStprs+1, 600 , DIR_High);
        //PORTB =0;
        //__delay_ms(50);
        //STPR_voidMoveStprStps (MyStprs+1, 600 , DIR_Low);
        // if (mymsg != -1 && mymsg!=-2) UART_TxArrMsg ((uint8 *)"I want to sleep", 16);
        //else UART_TxArrMsg ("ERROR", 6);
        //UART_TxMsgSyn  ('\n',100);
        //UART_TxMsgSyn  ('\r',100);
        //__delay_ms(20);



    }
    return;
}






void __interrupt(high_priority) high_isr(void)      // interrupt function ��� //Low priority interrupt������������ // High priority interrupt
{
        if(INTCONbits.T0IF && INTCONbits.T0IE) 
        {                                     // if timer flag is set & interrupt enabled
                TMR0H = 0x3C;
                TMR0L = 0xAF;               // reload the timer
                INTCONbits.T0IF = 0;                  // clear the interrupt flag 
                /*
                  Eeach interbval, the call back fn must be called
                  Use timer driver insted in the future...
                */
                STPR_callBack(MyStprs+1);
        }
}