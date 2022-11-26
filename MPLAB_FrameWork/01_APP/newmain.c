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
#include "EXTI_int.h"


/*HAL modules inc*/
#include "STPR_int.h"
#include "LCD_int.h"

/*APP modules*/
#include "mainH.h"


uint8 buffer[10];

/*first element represents the number of needed orders*/
/*the next 16 one are the max possiple actual orders*/
uint8 myOrders [MAX_ORDER_COUNT+1];

void main(void) {
    /*main counter*/
    uint8 i,item_index,count;
    sint8 TempVal,frstMsg;
    uint8 TempStr[4];
    /*Init the system HW modules*/
    INIT_SYS ();

    while (1)
    {
        LCD_SetCursor (1);
        LCD_wStr   ("    WELCOME    ");
        LCD_wStr   ("      MVM      ");
        __delay_ms(2000);

        
        do
        {
            //Get the temp value
            TempVal = GetNTC_temp(ADC_u16GetChannelReading(CHANNEL0));
            if (TempVal > HighTempLimit) DIO_VidSetPinValue(TempO_PORT, TempO_PIN, 1);
            if (TempVal < LowTempLimit) DIO_VidSetPinValue(TempO_PORT, TempO_PIN, 0);
            //PrintTemp(TempVal);

            /*Check if any data received*/
            frstMsg = UART_RxMsgSyn  (myTimeOutCount);

        }while ( frstMsg == FRAME_ERROR || frstMsg == RX_TIME_OUT);
        
        /*please receive an array of size myOrders[OrderSizeIndex] and put them in the array starting from FrstOrderIndex */
        UART_RxArrMsg  (myOrders+FrstOrderIndex, myOrders[OrderSizeIndex], myTimeOutCount);

        /*First frame is OrderSizeIndex, check it first*/
        if (  (uint8)frstMsg > MAX_ORDER_COUNT) myOrders[OrderSizeIndex] = MAX_ORDER_COUNT;
        else                                    myOrders[OrderSizeIndex] = (uint8)frstMsg;   
        /*Orders are recieved and all is OK*/

        /*Is there a person on the machine...?*/
        PersonExist = IS_SomeOneThere();
        if (!PersonExist) 
        {
            i = myTimeOutCount;
            while (--i) 
            {
                PersonExist = IS_SomeOneThere();
                __delay_ms(100);
            }
        }

        if (!PersonExist)
        {
            /*
              Send to ESP that no person is here
            */
            continue;
        } 
        /*
        Send back a notification of the successful message to ESP
        */
        UART_TxMsgSyn  (myOrders[OrderSizeIndex],0);

        

        /*There is a person waiting, start serving the order.. */
        LCD_SetCursor (1);
        LCD_wCmd   ("  PLEASE  WAIT     LOADING...   ");

        for (i=FrstOrderIndex; i <= myOrders[OrderSizeIndex]; i++)
        {
            /*First 4 bits are the index*/
            item_index = GET_NIBBLE(myOrders[i],0);
            /*Second four bits are the count needed from thet item*/
            count = GET_NIBBLE(myOrders[i],4);
            /*Move lever to the required item row*/
            moveLvr2Row(GET_ROW(item_index));
            /*Start feeding the item...*/
            STPR_voidMoveStprStps (&MyStprs[FrstStepperUniqueID+item_index], count*STPS_FOR_AN_ITEM , DIR_Low);
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






void __interrupt(high_priority) high_isr(void)     
{
    uint8 i;
    if(INTCONbits.T0IF && INTCONbits.T0IE) 
    {                                     // if timer flag is set & interrupt enabled
        TMR0H = 0x3C;
        TMR0L = 0xAF;               // reload the timer
        INTCONbits.T0IF = 0;                  // clear the interrupt flag 
        /*
            Eeach interval, the call back fn must be called
            Use timer driver instead in the future...
        */
        /*check for all steppers*/
        for (i=0;i<MySteppersNum;i++)STPR_callBack(MyStprs+i);
    }

    if(GET_BIT(INTCON,1)==1)                    //polling for INT0 interrupt
    { 
        STOP_STPRS_Emergancy();
        BIT_L(INTCON,1);                        //clearing INT0 interrupt flag
    }
   
}