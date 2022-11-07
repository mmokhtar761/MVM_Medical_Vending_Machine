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
void main(void) {

        /*Init the system HW modules*/
        void INIT_SYS (void)

        while (1)
                {
                //UART_TxMsgSyn  ('x',100);
                //mymsg = UART_RxMsgSyn  (10000);
                LCD_SetCursor (3);
                __delay_ms(20);
                LCD_wStr   ((uint8 *)"I am here");
                //while(1);
                //STPR_voidMoveStprStps (MyStprs+1, 600 , DIR_High);

                //__delay_ms(500);
                //STPR_voidMoveStprStps (MyStprs+1, 600 , DIR_Low);
                // if (mymsg != -1 && mymsg!=-2) UART_TxArrMsg ((uint8 *)"I want to sleep", 16);
                //else UART_TxArrMsg ("ERROR", 6);
                //UART_TxMsgSyn  ('\n',100);
                //UART_TxMsgSyn  ('\r',100);
                __delay_ms(2000);


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