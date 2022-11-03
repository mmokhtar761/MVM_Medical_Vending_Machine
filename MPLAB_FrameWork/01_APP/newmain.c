/*
 * File:   newmain.c
 * Author: Mohamed Mokhtar
 *
 * Created on 23 October 2022, 20:56
 */

#define _XTAL_FREQ 16000000
/*Lib modules inc*/
#include "Std_Types.h"
#include "Config_uC.h"
#include "MANIPULATOR.h"


/*MCAL modules inc*/
#include "DIO_int.h"
#include "UART_int.h"
void initT0Spaqitti(void);

/*HAL modules inc*/
#include "STPR_int.h"

/*Array of stepper handlers*/
STPR_type MyStprs [11];
sint8 mymsg;
void main(void) {
        /*Init MCAL modules*/
        DIO_Inti(); //Init pin dir as configured
        UART_voidInit ();
        initT0Spaqitti();//100ms simple timer
        /*Init HAL modules*/
        /*INIT all the steppers needed*/
        for (uint8 i=0; i<11;i++)
        {
                STPR_voidInitStpr (MyStprs+i,i,2,3000,900);
        }
        BIT_H(T0CON,7);  //timer on                          VAR|=  ((uint32)1<<BIT)
        ADCON1= 0b1110;
        PORTD =0;
        while (1)
        {
            //UART_TxMsgSyn  ('x',100);
            mymsg = UART_RxMsgSyn  (10000);

            //STPR_voidMoveStprStps (MyStprs+1, 600 , DIR_High);
            
           //__delay_ms(500);
           //STPR_voidMoveStprStps (MyStprs+1, 600 , DIR_Low);
           if (mymsg != -1 && mymsg!=-2) UART_TxArrMsg ("I want to sleep", 16);
           //else UART_TxArrMsg ("ERROR", 6);
            UART_TxMsgSyn  ('\n',100);
            UART_TxMsgSyn  ('\r',100);
           __delay_ms(2000);


        }
        
    return;
}


void initT0Spaqitti(void)
{
        /*Timer  50ms */
        TMR0H = 0x3C;
        TMR0L = 0xAF;
        T0CON = 0b00000011;
        INTCONbits.GIE=1;
        INTCONbits.T0IE =1;
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